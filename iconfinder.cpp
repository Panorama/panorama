#include "iconfinder.h"

QString IconFinder::findIcon(const QString &icon)
{
    //XXX This algorithm doesn't work in non-gconf environments
    //(but all desktops *should* have gconf by now)

    if(icon.contains("/")) //We have a resolved icon; quit
        return icon;
    else
    {
        //XXX The search index should be implemented as a tree
        foreach(const QDir &dir, _searchIndex) //Search the index
        {
            const QString file = findIconInDir(icon, dir);
            if(!file.isEmpty())
                return file;
        }
        return QString();
    }
}

QString IconFinder::findIconInDir(const QString &iconName, const QDir &dir)
{
    //This just shallowly searches for named files in the directory
    if(iconName.contains("."))
    {
        const QString fileName(dir.filePath(iconName));
        const QFileInfo info(fileName);
        if(info.exists() && info.isFile())
            return fileName;
    }
    else
    {
        foreach(const QString &suffix, _iconSuffixes)
        {
            QString name(iconName);
            name.append(suffix);
            const QString fileName(dir.filePath(name));

            const QFileInfo info(fileName);
            if(info.exists() && info.isFile())
                return fileName;
        }
    }
    return QString();
}

QString IconFinder::getParentTheme(const QDir &themeDir)
{
    QString result;
    QFile file(themeDir.filePath("index.theme"));

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return result;

    QTextStream in(&file);
    QString line;

    while(!in.atEnd() && !in.readLine().contains("[Icon Theme]"));

    while(!in.atEnd())
    {
        line = in.readLine();
        if(line.startsWith("#"))
            continue;
        else if(line.startsWith("Inherits="))
            return line.right(line.length() - 9); //9 == length of "Inherits="
        else if(line.startsWith("["))
            break;
    }
    file.close();
    return result;
}

QString IconFinder::findSystemTheme()
{
    QProcess gconftool;
    QStringList args;
    args << "--get" << "/desktop/gnome/interface/icon_theme";
    gconftool.start("gconftool-2", args);
    if(!gconftool.waitForStarted())
    {
        qWarning() << "The application \"gconftool-2\" couldn't be found";
        return QString();
    }

    gconftool.waitForFinished(1000);

    if(gconftool.state() == QProcess::NotRunning)
    {
        QString name(gconftool.readAllStandardOutput());
        name.chop(1);
        return name;
    }
    else
    {
        gconftool.kill();
        return QString();
    }
}

QStringList IconFinder::getDefaultThemePaths()
{
    QStringList result;
    QStringList tmp;
    tmp << QDir::root().filePath("usr") << "share" << "icons";
    result << QDir::home().filePath(".icons") << tmp.join(QDir::separator());
    return result;
}

QStringList IconFinder::getIconSuffixes()
{
    QStringList result;
    result << ".svg" << ".png"/* << ".xpm"*/; //Qt doesn't support XPM in WebKit
    return result;
}

QList<QDir> IconFinder::indexForTheme(const QString &name, const QStringList &paths,
                                      const QStringList &suffixes)
{
    QStringList filters;
    foreach(const QString &str, suffixes)
        filters += QString("*").append(str);

    return indexAllThemes(name, paths, filters);
}

QList<QDir> IconFinder::indexAllThemes(const QString &name, const QStringList &paths,
                                       const QStringList &filters)
{
    QList<QDir> result;

    QStringList tmp;
    tmp << QDir::root().filePath("tmp") << QString("panorama-iconindex-").append(name);

    const QString cacheFileName(tmp.join(QDir::separator()));
    bool rebuildCache(true);

    if(QFileInfo(cacheFileName).exists())
    {
        rebuildCache = false;
        QFile cachedIndex(cacheFileName);
        if(cachedIndex.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream in(&cachedIndex);
            while(!in.atEnd())
                result += in.readLine();
            cachedIndex.close();
        }
        else
            rebuildCache = true;
    }

    if(rebuildCache)
    {
        QStringList tmp;
        tmp << QDir::root().filePath("usr") << "share" << "pixmaps";
        result += QDir(tmp.join(QDir::separator()));
        indexTheme(name, paths, filters, result);
        indexTheme("hicolor", paths, filters, result);

        QFile cachedIndex(cacheFileName);
        if(cachedIndex.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&cachedIndex);

            foreach(const QDir &entry, result)
                out << entry.absolutePath() << endl;

            cachedIndex.flush();
            cachedIndex.close();
        }
        else
            qWarning() << "Could not open file " << cacheFileName;
    }
    return result;
}

void IconFinder::indexTheme(const QString &name, const QStringList &paths,
                            const QStringList &filters, QList<QDir> &result)
{
    foreach(const QString &path, paths)
    {
        QDir dir(path);
        if(dir.cd(name))
        {
            if(dir.entryInfoList(filters, QDir::Files).count() > 0)
                result += QDir(dir);
            indexSubdir(dir, filters, result);
            QString super = getParentTheme(dir);
            if(!super.isEmpty())
                indexTheme(super, paths, filters, result);
        }
    }
}

void IconFinder::indexSubdir(const QDir &dir, const QStringList &filters,
                             QList<QDir> &result)
{
    QStringList subdirs = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot,
                                        QDir::Name | QDir::Reversed);
    QMap<int, QStringList> costs;
    foreach(const QString &d, subdirs)
    {
        if(d.at(0).isDigit())
        {
            QString &dimStr = d.split("x")[0];
            bool ok;
            int dim = dimStr.toInt(&ok, 10);
            if(ok)
                costs[abs(64 - dim)] += d; //We want 64x64 icons... prefer "scalable" if they are larger than that
            else
                costs[0] += d;
        }
        else if (d == "scalable")
            costs[0] += d;
        else
            costs[1024] += d;
    }
    QList<int> keys = costs.keys();
    qSort(keys);

    foreach(const int key, keys)
        foreach(const QString &d, costs[key])
        {
            const QDir subdir(dir.filePath(d));
            if(subdir.entryList(filters, QDir::Files).count() > 0)
                result += subdir;
            if(subdir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).count() > 0)
                indexSubdir(subdir, filters, result);
        }
}

QString IconFinder::_themeName = findSystemTheme();
QStringList IconFinder::_themePaths = getDefaultThemePaths();
QStringList IconFinder::_iconSuffixes = getIconSuffixes();
QList<QDir> IconFinder::_searchIndex = indexForTheme(_themeName, _themePaths, _iconSuffixes);
