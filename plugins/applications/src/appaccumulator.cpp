#include "appaccumulator.h"

#include <QString>
#include <QDateTime>
#include <QFileSystemWatcher>
#include <QHash>
#include <QList>
#include <QObject>
#include <QStringList>
#include <QDir>
#include <QFileInfo>

#include "pndscanner.h"
#include "desktopfile.h"

class AppAccumulatorPrivate
{
    PANORAMA_DECLARE_PUBLIC(AppAccumulator)
public:
    struct FileInfo {
    public:
        QString name;
        QDateTime lastModified;
        FileInfo(const QString &name, const QDateTime &lastModified)
        {
            this->name = name;
            this->lastModified = lastModified;
        }
    };

    void addViaDesktopFile(const QString &file, bool initial = false);
    void removeViaDesktopFile(const QString &file);
    bool shouldAddThisApp(const QString &file) const;

    QFileSystemWatcher watcher;
    QHash<QString, QList<FileInfo> > currentFileInfos;
    QHash<QString, Application> apps;
};


AppAccumulator::AppAccumulator(QObject *parent) :
    QObject(parent)
{
    PANORAMA_INITIALIZE(AppAccumulator);
    //Reload any changed file in any searchpath
    connect(&priv->watcher, SIGNAL(directoryChanged(QString)),
            this, SLOT(rescanDir(QString)));

    //Load PNDs preemptively
    PndScanner::scanPnds();
}

AppAccumulator::~AppAccumulator()
{
    PANORAMA_UNINITIALIZE(AppAccumulator);
}

void AppAccumulator::loadFrom(const QStringList &searchpaths, const bool initial)
{
    PANORAMA_PRIVATE(AppAccumulator);
    //Scan all search paths
    foreach(const QString &path, searchpaths)
    {
        const QDir dir(path);
        foreach(const QString &file, dir.entryList(QStringList("*.desktop")))
        {
            const QString desktopFile(dir.filePath(file));
            priv->addViaDesktopFile(desktopFile, initial);

            priv->currentFileInfos[path] +=
                    AppAccumulatorPrivate::FileInfo(file, QFileInfo(desktopFile).lastModified());
        }

        //Scan recursively
        QStringList subPaths;
        foreach(const QString &subdir, dir.entryList(QDir::Dirs |
                                                     QDir::NoDotAndDotDot))
        {
            subPaths += dir.filePath(subdir);
        }
        if(subPaths.count() > 0)
            loadFrom(subPaths);
    }
    if(initial)
        emit finishedInitialLoad();

    priv->watcher.addPaths(searchpaths);
}

Application AppAccumulator::getApplication(const QString &id) const
{
    PANORAMA_PRIVATE(const AppAccumulator);
    return priv->apps[id];
}

void AppAccumulator::rescanDir(const QString &d)
{
    PANORAMA_PRIVATE(AppAccumulator);
    const QDir dir(d);
    const QStringList files = dir.entryList(QStringList("*.desktop"));
    QStringList diff(files); //== (files - oldFiles) conceptually

    //We assume that the pnd daemon has done its job and removed .desktop files
    //after PNDs havebeen removed. We don't want to interfere *while* the PNDs
    //are moved around...
    PndScanner::scanPnds();

    QList<AppAccumulatorPrivate::FileInfo> newFiles;

    //Check if files were added, removed or updated
    foreach(const AppAccumulatorPrivate::FileInfo &oldFile, priv->currentFileInfos[d])
    {
        if(files.contains(oldFile.name)) //File existed and still exists
        {
            QDateTime lm =
                    QFileInfo(dir.filePath(oldFile.name)).lastModified();
            if(oldFile.lastModified < lm)
            {
                const QString f(dir.filePath(oldFile.name));
                priv->removeViaDesktopFile(f);
                priv->addViaDesktopFile(f);

                //Retain file with new time stamp
                newFiles += AppAccumulatorPrivate::FileInfo(oldFile.name, lm);
            }
            else
            {
                newFiles += oldFile;
            }

            //Remove "new file mark"
            diff.removeOne(oldFile.name);
        }
        else
            //Remove file
            priv->removeViaDesktopFile(dir.filePath(oldFile.name));
    }

    //Create TrackedFiles for the new files
    foreach(const QString &diffElem, diff)
    {
        AppAccumulatorPrivate::FileInfo file(diffElem, QFileInfo(dir.filePath(diffElem)).lastModified());

        priv->addViaDesktopFile(dir.filePath(file.name));
        newFiles += file;
    }

    priv->currentFileInfos[d] = newFiles;
}

void AppAccumulatorPrivate::removeViaDesktopFile(const QString &f)
{
    PANORAMA_PUBLIC(AppAccumulator);
    //Find the app to remove by file name and remove it
    foreach(const QString &key, apps.keys())
    {
        const Application &app(apps[key]);
        if(app.relatedFile == f)
        {
            emit pub->appRemoved(app);
            apps.remove(key);
            return;
        }
    }
}

bool AppAccumulatorPrivate::shouldAddThisApp(const QString &f) const
{
    foreach(const Application &app, apps.values())
    {
        if(app.relatedFile == f)
            return false;
    }
    return true;
}

void AppAccumulatorPrivate::addViaDesktopFile(const QString &f, const bool initial)
{
    PANORAMA_PUBLIC(AppAccumulator);
    if(shouldAddThisApp(f))
    {
        Application result = DesktopFile(f).readToApplication();
        if(!result.name.isEmpty() && !result.id.isEmpty())
        {
            //Enables us to filter out applications without categories
            if(result.categories.isEmpty())
                result.categories.append("NoCategory");

            apps[result.id] = result;

            // If this is the initial scan, don't emit anything.
            emit pub->appAdded(result, !initial);
        }
    }
}
