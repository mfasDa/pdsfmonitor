#include "qapplication.h"
#include "qjsondocument.h"
#include "qjsonarray.h"
#include "qjsonobject.h"
#include "qlabel.h"
#include "qtableview.h"
#include "qstandarditemmodel.h"
#include <iterator>

#include "pdsfmonitormain.h"
#include "ui_pdsfmonitormain.h"
#include "nersclogindialog.h"
#include "nersclogindata.h"
#include "nerscjobdata.h"
#include "newtrequest.h"
#include "pdsfjob.h"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <sstream>

namespace PDSFApplication {

PDSFMonitorMain::PDSFMonitorMain(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PDSFMonitorMain),
    fLoginData(NULL),
    fJobData(NULL)
{
    ui->setupUi(this);

    //
    ui->fUpdateButten->setEnabled(false);
    ui->fPDSFstatusButton->setEnabled(false);
    // Login label
    ui->fLoginLabel->setText("status: Not logged in");
    ui->fLoginLabel->setStyleSheet("QLabel {color: red}");

    // Job table
    InitJobtable(ui->fJobTable);
}

PDSFMonitorMain::~PDSFMonitorMain()
{
    delete ui;
}

void PDSFMonitorMain::on_fExitButton_clicked()
{
    if(fLoginData && fLoginData->IsLoggedIn())
        Logout();
    QApplication::quit();
}

void PDSFMonitorMain::on_fLoginButton_clicked()
{
    NERSCLoginDialog *loginDialog = new NERSCLoginDialog(this);
    loginDialog->setVisible(true);
}

void PDSFMonitorMain::ReturnFromLogin(NERSCLoginDialog *dialog){
   fLoginData = dialog->GetLoginData();
   dialog->setVisible(false);
   if(fLoginData){
       if(fLoginData->IsLoggedIn()){
           std::stringstream logintextbuilder;
           logintextbuilder << "Welcome " << fLoginData->GetUserName();
           ui->fLoginLabel->setText(logintextbuilder.str().c_str());
           ui->fLoginLabel->setStyleSheet("QLabel {color:green}");
           ui->fUpdateButten->setEnabled(true);
           // Fetch my jobs from nersc
            UpdateJobStatus();
       }
   }
}

void PDSFMonitorMain::UpdateJobStatus(){
    std::stringstream urlbuilder;
    urlbuilder << "https://newt.nersc.gov/newt/queue/pdsf/?user=" << fLoginData->GetUserName();
    //std::cout << "Request: " << urlbuilder.str() << std::endl;
    NEWT::NEWTRequest request(urlbuilder.str(), "", NEWT::NEWTRequest::kGET, NEWT::NEWTRequest::kRead, fLoginData->GetCookie());
    QJsonDocument answer = QJsonDocument::fromJson(QString(request.GetNERSCResponse().c_str()).toUtf8());
    if(!fJobData)
        fJobData = new NEWT::NERSCJobData();
    else
        fJobData->Reset();
    QJsonArray jobarray = answer.array();
    foreach(const QJsonValue jobiter, jobarray){
        QJsonObject jsonjob = jobiter.toObject();

        NEWT::PDSFJob foundjob;
        foundjob.SetJobStatus(jsonjob.value(QString("status")).toString().toUtf8().data());
        foundjob.SetUser(jsonjob.value(QString("user")).toString().toUtf8().data());
        foundjob.SetJobName(jsonjob.value(QString("name")).toString().toUtf8().data());
        foundjob.SetQueue(jsonjob.value(QString("queue")).toString().toUtf8().data());
        foundjob.SetJobID(atoi(jsonjob.value(QString("jobid")).toString().toUtf8().data()));
        foundjob.SetPriority(jsonjob.value(QString("priority")).toDouble());
        // parse starttime
        std::stringstream timestring;
        timestring << std::string(jsonjob.value(QString("startday")).toString().toUtf8().data())
                   << " "
                   << std::string(jsonjob.value(QString("starttime")).toString().toUtf8().data());
        struct tm starttime;
        strptime(timestring.str().c_str(), "%m/%d/%Y %H:%M:%S", &starttime);
        foundjob.SetStartTime(starttime);
        fJobData->InsertPDSFJob(foundjob);
    }

    // add jobs to table
    QStandardItemModel *jobtablemodel = static_cast<QStandardItemModel *>(ui->fJobTable->model());
    //jobtablemodel->clear();
    std::vector<NEWT::PDSFJob> myjobs = fJobData->GetJobsForUser(fLoginData->GetUserName(), NEWT::NERSCJobData::kAll);
    int numberrows = std::max(int(myjobs.size()), 10);
    for(int krow = 0; krow < numberrows; krow++){
        jobtablemodel->setData(jobtablemodel->index(krow, 0), QString(""));
        jobtablemodel->setData(jobtablemodel->index(krow, 1), QString(""));
        jobtablemodel->setData(jobtablemodel->index(krow, 2), QString(""));
    }
    jobtablemodel->setRowCount(numberrows);
    int irow = 0;
    for(std::vector<NEWT::PDSFJob>::iterator pdsfjobiter = myjobs.begin(); pdsfjobiter != myjobs.end(); ++pdsfjobiter){
        jobtablemodel->setData(jobtablemodel->index(irow, 0), QString::number(pdsfjobiter->GetJobID()));
        jobtablemodel->setData(jobtablemodel->index(irow, 1), QString(pdsfjobiter->GetJobName().c_str()));
        jobtablemodel->setData(jobtablemodel->index(irow, 2), QString(pdsfjobiter->GetJobStatus().c_str()));
        irow++;
    }
}

void PDSFMonitorMain::Logout(){
    NEWT::NEWTRequest logoutrequest("https://newt.nersc.gov/newt/logout", "", NEWT::NEWTRequest::kGET,NEWT::NEWTRequest::kRead, fLoginData->GetCookie());
    // Check that logout was successfull
    QJsonDocument response = QJsonDocument::fromJson(QString(logoutrequest.GetNERSCResponse().c_str()).toUtf8());
    bool authstatus = response.object().value("auth").toBool();
    if(!authstatus){
        std::cout << "successfully logged out" << std::endl;
    } else {
        std::cout << "problem logging out" << std::endl;
    }
    // delete cookie
    if(fLoginData->GetCookie().length()) remove(fLoginData->GetCookie().c_str());
}

void PDSFMonitorMain::InitJobtable(QTableView *jobtable){
    QStandardItemModel *tablemodel = new QStandardItemModel(10, 3, this);
    tablemodel->setHorizontalHeaderItem(0, new QStandardItem(QString("ID")));
    tablemodel->setHorizontalHeaderItem(1, new QStandardItem(QString("Jobname")));
    tablemodel->setHorizontalHeaderItem(2, new QStandardItem(QString("Status")));
    jobtable->setModel(tablemodel);

    jobtable->setColumnWidth(0, 230);
    jobtable->setColumnWidth(1, 260);
    jobtable->setColumnWidth(2, 90);
}

}

void PDSFApplication::PDSFMonitorMain::on_fUpdateButten_clicked()
{
    if(fLoginData && fLoginData->IsLoggedIn())
        UpdateJobStatus();
}

void PDSFApplication::PDSFMonitorMain::on_fJobTable_clicked(const QModelIndex &index)
{
    QStandardItemModel *tablemodel = static_cast<QStandardItemModel *>(ui->fJobTable->model());
    int jobid = tablemodel->data(tablemodel->index(index.row(), 0)).toInt();
    std::stringstream requeststring;
    requeststring << "https://newt.nersc.gov/newt/queue/pdsf/" << jobid;
    NEWT::NEWTRequest request(requeststring.str(), "", NEWT::NEWTRequest::kGET, NEWT::NEWTRequest::kRead, fLoginData->GetCookie());
}
