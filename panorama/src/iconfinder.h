#ifndef ICONFINDER_H
#define ICONFINDER_H

#include <QString>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QProcess>
#include <QImageReader>
#include <QDebug>

/**
 * A helper class that resolves icons from Free Desktop Foundation Icon Themes
 */
class IconFinder
{
public:
    /**
     * Finds a named icon. Will return immediately if the icon is resolved
     * already
     */
    static QString findIcon(const QString &iconName, const QString &fallback = "");
};

#endif // ICONFINDER_H
