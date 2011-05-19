#include <QtGui/QApplication>
#include "mainwindow.h"

#include "setting.h"

int main(int argc, char *argv[])
{
    QApplication::setGraphicsSystem("raster");

    //We don't have any args, but pass them on anyways for standard X.Org args
    //handling
    const QApplication a(argc, argv);

    qmlRegisterType<Setting>("Panorama",1,0,"Setting");

    //Show the main window
    MainWindow w;
    w.show();

    //Run the event loop
    return a.exec();
}
