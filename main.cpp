#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //We don't have any args, but pass them on anyways for standard X.Org args handling
    const QApplication a(argc, argv);

    //Show the main window
    MainWindow w;
    w.show();

    //Run the event loop
    return a.exec();
}
