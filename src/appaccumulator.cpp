#include "appaccumulator.h"

AppAccumulator::AppAccumulator(QObject *parent) :
    QObject(parent)
{
    //Reload any changed file in any searchpath
    connect(&_watcher, SIGNAL(directoryChanged(QString)), this, SLOT(watchedDirUpdated(QString)));

    //Load PNDs preemptively
    PndScanner::scanPnds();
}

void AppAccumulator::loadFrom(const QStringList &searchpaths)
{
    //Scan all search paths
    foreach(const QString &path, searchpaths)
    {
        const QDir dir(path);
        foreach(const QString &file, dir.entryList(QStringList("*.desktop")))
        {
            const QString desktopFile(dir.filePath(file));
            addViaDesktopFile(desktopFile);

            FileInfo *tf = new FileInfo;
            tf->file = file;
            tf->lastModified = QFileInfo(desktopFile).lastModified();
            _currentFileInfos[path] += tf;
        }

        //Scan recursively
        QStringList subPaths;
        foreach(const QString &subdir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
        {
            subPaths += dir.filePath(subdir);
        }
        if(subPaths.count() > 0)
            loadFrom(subPaths);
    }
    _watcher.addPaths(searchpaths);
}

QString AppAccumulator::getExecLine(const QString &key)
{
    return _execs[key];
}

void AppAccumulator::watchedDirUpdated(const QString &d)
{
    QDir dir(d);
    const QStringList files = dir.entryList(QStringList("*.desktop"));
    QStringList diff(files); //== (files - oldFiles) conceptually

    //We assume that the pnd daemon has done its job and removed .desktop files
    //after PNDs havebeen removed. We don't want to interfere *while* the PNDs
    //are moved around...
    PndScanner::scanPnds();

    QList<FileInfo*> &oldFiles = _currentFileInfos[d];
    QList<FileInfo*> toAdd;
    QList<FileInfo*> toUpdate;
    QList<FileInfo*> toRemove;

    //Check if files were added, removed or updated
    foreach(FileInfo *oldFile, oldFiles)
    {
        if(files.contains(oldFile->file)) //File existed and still exists
        {
            QDateTime lm = QFileInfo(dir.filePath(oldFile->file)).lastModified();
            if(oldFile->lastModified < lm)
            {
                //Mark for update
                toUpdate += oldFile;

                //Update time stamp
                oldFile->lastModified = lm;
            }

            //Remove "new file mark"
            diff.removeOne(oldFile->file);
        }
        else
            //Mark for removal
            toRemove += oldFile;
    }

    //Create TrackedFiles for the new files
    foreach(const QString &diffElem, diff)
    {
        FileInfo *tf = new FileInfo;
        tf->file = diffElem;
        tf->lastModified = QFileInfo(dir.filePath(diffElem)).lastModified();
        toAdd += tf;
    }

    foreach(FileInfo *file, toAdd)
    {
        addViaDesktopFile(dir.filePath(file->file));
        oldFiles.append(file);
    }

    foreach(const FileInfo *file, toUpdate)
    {
        const QString f(dir.filePath(file->file));
        removeViaDesktopFile(f);
        addViaDesktopFile(f);
    }

    foreach(FileInfo *file, toRemove)
    {
        removeViaDesktopFile(dir.filePath(file->file));
        oldFiles.removeOne(file);
        delete file;
    }
}

void AppAccumulator::removeViaDesktopFile(const QString &f)
{
    //Find the app to remove by file name and remove it
    for(int i = 0; i < _apps.count(); i++)
    {
        const Application &app(_apps.at(i));
        if(app.relatedFile == f)
        {
            emit appRemoved(app);
            _execs.remove(app.id);
            _apps.removeAt(i);
            return;
        }
    }
}

bool AppAccumulator::shouldAddThisApp(const QString &f) const
{
    foreach(const Application &app, _apps)
    {
        if(app.relatedFile == f)
            return false;
    }
    return true;
}

void AppAccumulator::addViaDesktopFile(const QString &f)
{
    if(shouldAddThisApp(f))
    {
        Application result = DesktopFile(f).readToApplication();
        if(!result.name.isEmpty() && !result.id.isEmpty())
        {
            QString oldExec = result.id;
            result.id = QCryptographicHash::hash(oldExec.toLocal8Bit(), QCryptographicHash::Sha1).toHex();
            _apps += result;
            _execs[result.id] = oldExec;
            emit appAdded(result);
        }
    }
}

QHash<QString, QString>AppAccumulator::_execs;
