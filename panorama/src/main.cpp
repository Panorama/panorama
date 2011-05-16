#include <QtGui/QApplication>
#include "mainwindow.h"

#include "panoramaui.h"
#include "setting.h"
#include "systeminformation.h"
#include "pandora.h"

int main(int argc, char *argv[])
{
    QApplication::setGraphicsSystem("raster");

    //We don't have any args, but pass them on anyways for standard X.Org args
    //handling
    const QApplication a(argc, argv);

    qmlRegisterType<PanoramaUI>("Panorama", 1,0, "PanoramaUI");
    qmlRegisterType<Setting>("Panorama",1,0,"Setting");
    qmlRegisterType<SystemInformation>("Panorama",1,0,"SystemInformation");
    qmlRegisterType<Pandora>("Panorama",1,0,"Pandora");

    //Show the main window
    MainWindow w;
    w.show();

    //Run the event loop
    return a.exec();
}
