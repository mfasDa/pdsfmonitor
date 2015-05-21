#include "aboutdialog.h"
#include "pdsfmonitormain.h"
#include "ui_aboutdialog.h"
namespace PDSFApplication{

AboutDIalog::AboutDIalog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDIalog)
{
    ui->setupUi(this);
}

AboutDIalog::~AboutDIalog()
{
    delete ui;
}

}

void PDSFApplication::AboutDIalog::on_CloseButton_clicked()
{
    PDSFMonitorMain *parentmod = static_cast<PDSFMonitorMain *>(parent());
    parentmod->ReturnFromAbout(this);
}
