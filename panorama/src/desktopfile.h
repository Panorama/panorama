#ifndef DESKTOPFILE_H
#define DESKTOPFILE_H

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

/**
 * Represents a FDF .desktop file
 */
class DesktopFile
{
public:
    /**
     * Constructs a new DesktopFile instance, using the specified .desktop
     * file
     */
    DesktopFile(const QString &file);

    /**
     * Reads the contents of the attached .desktop file into an Application
     * instance
     */
    Application readToApplication();

private:
    static QString readLocalized(const QMap<QString, QVariant> &map, const QString &fieldName);
    static QMap<QString, QVariant> parseDesktop(const QString &file);

    QString _file;

    static const QString EXEC_FIELD;
    static const QString NAME_FIELD;
    static const QString COMMENT_FIELD;
    static const QString ICON_FIELD;
    static const QString VERSION_FIELD;
    static const QString PANDORA_UID_FIELD;
    static const QString CATEGORIES_FIELD;
    static const QString TYPES_FIELD;
    static const QString APPLICATION_TYPE;
    static const QString FIELD_TEMPLATE;
};

#endif // DESKTOPFILE_H
