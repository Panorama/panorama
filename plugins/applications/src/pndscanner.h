#ifndef PNDSCANNER_H
#define PNDSCANNER_H

#include <QString>

#include "pnd.h"

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
    PndScanner() {}

    PndScanner(const PndScanner&);

    PndScanner& operator=(const PndScanner&);
};

#endif // PNDSCANNER_H
