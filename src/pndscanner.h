#ifndef PNDSCANNER_H
#define PNDSCANNER_H

#include <QDebug>
#include <pnd_conf.h>
#include <pnd_apps.h>
#include <pnd_container.h>
#include <pnd_discovery.h>
#include "pnd.h"

//I'm trying to keep the coupling between libpnd←→Panorama s loose as possible,
//because ther might come API changes in the future...

class PndScanner
{
public:
    static void scanPnds();
    static Pnd pndForUID(const QString &uid);

private:
    PndScanner() {};
    PndScanner(const PndScanner&);
    PndScanner& operator=(const PndScanner&);
    static QList<Pnd> _pnds;
};

#endif // PNDSCANNER_H
