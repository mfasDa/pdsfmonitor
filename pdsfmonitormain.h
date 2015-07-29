/***************************************************************************
 * Simple monitoring program for the PDSF cluster at NERSC using NEWT.     *
 * Copyright (C) 2015  Markus Fasel, Lawrence Berkeley National Laboratory *
 *                                                                         *
 * This program is free software: you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation, either version 3 of the License, or       *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 ***************************************************************************/

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

class AboutDIalog;
class NERSCLoginDialog;

class PDSFMonitorMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit PDSFMonitorMain(QWidget *parent = 0);
    ~PDSFMonitorMain();

    void ReturnFromLogin(NERSCLoginDialog *dialog);
    void ReturnFromAbout(AboutDIalog *dialog);

protected:

    void InitJobtable(QTableView *jobtable);
    void UpdateJobStatus();
    void Logout();

private slots:
    void on_fExitButton_clicked();

    void on_fLoginButton_clicked();

    void on_fUpdateButten_clicked();

    void on_fJobTable_clicked(const QModelIndex &index);

    void on_actionAbout_triggered();

private:
    Ui::PDSFMonitorMain                 *ui;
    NEWT::NERSCLoginData                *fLoginData;
    NEWT::NERSCJobData                  *fJobData;
};

}

#endif // PDSFMONITORMAIN_H
