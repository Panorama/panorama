#ifndef APPACCUMULATOR_H
#define APPACCUMULATOR_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QList>
#include <QFileSystemWatcher>
#include <QDateTime>

#include "application.h"
#include "desktopfile.h"

/**
 * Scans a set of search paths, finds all of the .desktop files in those search
 * paths and generates Application instances based on the found desktop files.
 *
 * It is not necessary to call "loadFrom" multiple times; INotify is used to
 * send out updated application instances automatically when a file changes.
 */
class AppAccumulator : public QObject
{
Q_OBJECT
public:
    /** Constructs a new AppAccumulator instance */
    explicit AppAccumulator(QObject *parent = 0);

    /** Loads all .desktop files from the specified search paths (not recursive) */
    void loadFrom(const QStringList &searchpaths);

signals:
    /** An application has been found or added to one of the search paths */
    void appAdded(const Application &app);

    /** An application has been removed from one of the search paths */
    void appRemoved(const Application &app);

private slots:
    void watchedDirUpdated(const QString &dir);

private:
    struct FileInfo {
        QString file;
        QDateTime lastModified;
    };

    void addViaDesktopFile(const QString &file);
    void removeViaDesktopFile(const QString &file);
    bool shouldAddThisApp(const QString &file) const;

    QFileSystemWatcher _watcher;
    QList<Application> _apps;
    QHash<QString, QList<FileInfo *> > _currentFileInfos;
};

#endif // APPACCUMULATOR_H
