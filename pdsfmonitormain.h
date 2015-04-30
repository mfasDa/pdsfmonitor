#ifndef PDSFMONITORMAIN_H
#define PDSFMONITORMAIN_H

#include <QMainWindow>

class QTableView;

namespace Ui {
class PDSFMonitorMain;
}

namespace NEWT{
class NERSCLoginData;
class NERSCJobData;
}

namespace PDSFApplication{

class NERSCLoginDialog;

class PDSFMonitorMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit PDSFMonitorMain(QWidget *parent = 0);
    ~PDSFMonitorMain();

    void ReturnFromLogin(NERSCLoginDialog *dialog);

protected:

    void InitJobtable(QTableView *jobtable);
    void UpdateJobStatus();
    void Logout();

private slots:
    void on_fExitButton_clicked();

    void on_fLoginButton_clicked();

    void on_fUpdateButten_clicked();

private:
    Ui::PDSFMonitorMain                 *ui;
    NEWT::NERSCLoginData                *fLoginData;
    NEWT::NERSCJobData                  *fJobData;
};

}

#endif // PDSFMONITORMAIN_H
