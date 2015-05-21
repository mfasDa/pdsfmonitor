#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>

namespace Ui {
class AboutDIalog;
}
namespace PDSFApplication{


class AboutDIalog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDIalog(QWidget *parent = 0);
    ~AboutDIalog();

private slots:
    void on_CloseButton_clicked();

private:
    Ui::AboutDIalog *ui;
};

}

#endif // ABOUTDIALOG_H
