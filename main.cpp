#include "mainwindow.h"
#include "secdialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //secDialog dialog;
    //dialog.show();
    return a.exec();
}
