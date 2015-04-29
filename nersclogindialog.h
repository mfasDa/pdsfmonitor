#ifndef NERSCLOGINDIALOG_H
#define NERSCLOGINDIALOG_H

#include <QDialog>

class NERSCLoginData;
class QAbstractButton;

namespace NEWT {
class NERSCLoginData;
}

namespace Ui {
class NERSCLoginDialog;
}

namespace PDSFApplication {

class NERSCLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NERSCLoginDialog(QWidget *parent = 0);
    ~NERSCLoginDialog();

    NEWT::NERSCLoginData *GetLoginData() const { return fLoginData; }

private slots:
    void on_fDialogButtons_clicked(QAbstractButton *button);

protected:
    void HandleOK();
    void HandleCancel();

private:
    Ui::NERSCLoginDialog            *ui;
    NEWT::NERSCLoginData            *fLoginData;
};

}

#endif // NERSCLOGINDIALOG_H
