#include "nersclogindialog.h"
#include "nersclogindata.h"
#include "newtrequest.h"
#include "pdsfmonitormain.h"
#include "ui_nersclogindialog.h"

#include <cstdlib>
#include <iostream>
#include <sstream>

#include <qabstractbutton.h>
#include <qdialogbuttonbox.h>
#include <qjsondocument.h>
#include <qjsonvalue.h>
#include <qjsonobject.h>

namespace PDSFApplication {

///
/// \brief NERSCLoginDialog::NERSCLoginDialog
/// \param parent
///
NERSCLoginDialog::NERSCLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NERSCLoginDialog),
    fLoginData(NULL)
{
    ui->setupUi(this);
    ui->fUsernameField->setFocus();
}

///
/// \brief NERSCLoginDialog::~NERSCLoginDialog
///
/// Destructor
///
NERSCLoginDialog::~NERSCLoginDialog()
{
    delete ui;
}

///
/// \brief NERSCLoginDialog::on_buttonBox_clicked
/// \param button
///
void NERSCLoginDialog::on_fDialogButtons_clicked(QAbstractButton *button)
{
    QDialogButtonBox::StandardButton stdbutton = ui->fDialogButtons->standardButton(button);
    switch(stdbutton){
    case QDialogButtonBox::Ok:
        HandleOK();
        break;
    case QDialogButtonBox::Cancel:
        HandleCancel();
        break;
    }
}

///
/// \brief NERSCLoginDialog::HandleOK
///
void NERSCLoginDialog::HandleOK(){
    if(!fLoginData)
        fLoginData = new NEWT::NERSCLoginData(static_cast<const char *>(ui->fUsernameField->text().toUtf8().constData()),
                                        static_cast<const char *>(ui->fPasswordField->text().toUtf8().constData()));
    else {
        fLoginData->SetUserName(static_cast<const char *>(ui->fUsernameField->text().toUtf8().constData()));
        fLoginData->SetPassword(static_cast<const char *>(ui->fPasswordField->text().toUtf8().constData()));
    }

    // Send login request
    std::stringstream postparams;
    postparams << "username=" << fLoginData->GetUserName() << "&password=" << fLoginData->GetPassword();
    std::stringstream cookiefile;
    cookiefile << "/tmp/newt_" << fLoginData->GetUserName() << "_" << rand() % 100000;
    NEWT::NEWTRequest loginrequest("https://newt.nersc.gov/newt/auth", postparams.str() , NEWT::NEWTRequest::kPOST, NEWT::NEWTRequest::kWrite, cookiefile.str());

    QJsonDocument jsondoc = QJsonDocument::fromJson(QString(loginrequest.GetNERSCResponse().c_str()).toUtf8());
    QJsonObject o = jsondoc.object();
    fLoginData->SetLoggedIn(o.value(QString("auth")).toBool());
    fLoginData->SetSessionID(static_cast<char *>(o.value("newt_sessionid").toString().toUtf8().data()));
    fLoginData->SetSessionLifetime(o.value(QString("session_lifetime")).toInt());
    fLoginData->SetCookie(loginrequest.GetCookie());
    if(fLoginData->IsLoggedIn()){
        // User successfully logged in - close window
        std::cout << "Successfully logged in" << std::endl;
        PDSFMonitorMain *parentmod = static_cast<PDSFMonitorMain *>(parent());
        parentmod->ReturnFromLogin(this);
    } else {
        std::cout << "Login failure" << std::endl;
        // Login failed - display to user
        ui->fStatusLabel->setText("authentication failed");
    }
}

///
/// \brief NERSCLoginDialog::HandleCancel
///
void NERSCLoginDialog::HandleCancel(){
    PDSFMonitorMain *parentmod = static_cast<PDSFMonitorMain *>(parent());
    parentmod->ReturnFromLogin(this);
}

}

