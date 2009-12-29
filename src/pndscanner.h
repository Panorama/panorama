#ifndef PNDSCANNER_H
#define PNDSCANNER_H

#include <QDebug>
#include <pnd_conf.h>
#include <pnd_apps.h>
#include <pnd_container.h>
#include <pnd_discovery.h>
#include "pnd.h"

//I'm trying to keep the coupling between libpnd←→Panorama as loose as possible,
//because ther might come API changes in the future...

/**
 * A class for scanning the file system for PNDs, using libpnd's search system
 */
class PndScanner
{
public:
    /** Scans the file system for PNDs */
    static void scanPnds();

    /** Retrieves a PND file for the given pandora uid */
    static Pnd pndForUID(const QString &uid);

private:
    PndScanner() {};

    PndScanner(const PndScanner&);

    PndScanner& operator=(const PndScanner&);

    static QList<Pnd> _pnds;
};

#endif // PNDSCANNER_H
