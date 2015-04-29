#include "pdsfmonitormain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PDSFApplication::PDSFMonitorMain w;
    w.show();

    return a.exec();
}
