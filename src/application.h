#ifndef APPLICATION_H
#define APPLICATION_H

#include <QMetaType>
#include <QString>
#include <QStringList>

/**
 * Represents a launchable application
 */
struct Application
{
    /** The SHA1 ID of this application */
    QString id;

    /** The PND id that this application is related to */
    QString pandoraId;

    /** The file that the application was loaded from */
    QString relatedFile;

    /** The human-readable name of the application */
    QString name;

    /** The application comment (mostly the description) */
    QString comment;

    /** The application icon path */
    QString icon;

    /** The application's version */
    QString version;

    /** The path to the application's preview image */
    QString preview;

    /** The recommended clockspeed for the applicaiton */
    int clockspeed;

    /** A list of Free Desktop Foundation caetgories that this application belongs to */
    QStringList categories;

    /** Compares one Application instance to another */
    bool operator ==(const Application &that) const;
};

#endif // APPLICATION_H
