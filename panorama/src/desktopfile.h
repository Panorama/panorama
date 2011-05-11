#ifndef DESKTOPFILE_H
#define DESKTOPFILE_H

#include "panoramainternal.h"

#include <QString>
#include <QFile>
#include <QLocale>
#include <QTextStream>
#include <QDebug>
#include <QtCore/QSettings>

#include "application.h"
#include "iconfinder.h"
#include "pndscanner.h"
#include "pnd.h"

class DesktopFilePrivate;

/**
 * Represents a FDF .desktop file
 */
class DesktopFile
{
    PANORAMA_DECLARE_PRIVATE(DesktopFile)
public:
    /**
     * Constructs a new DesktopFile instance, using the specified .desktop
     * file
     */
    DesktopFile(const QString &file);
    ~DesktopFile();

    /**
     * Reads the contents of the attached .desktop file into an Application
     * instance
     */
    Application readToApplication();
};

#endif // DESKTOPFILE_H
