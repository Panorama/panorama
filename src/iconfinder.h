#ifndef ICONFINDER_H
#define ICONFINDER_H

#include <QString>
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QProcess>
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
    static QString findIcon(const QString &iconName);

private:
    IconFinder() {};
    IconFinder(const IconFinder&);
    IconFinder& operator=(const IconFinder&);

    static QString findIconInDir(const QString &iconName, const QDir &themeDir);

    static QString getParentTheme(const QDir &themeDir);

    static QString findSystemTheme();

    static QStringList getDefaultThemePaths();

    static QStringList getIconSuffixes();

    static QList<QDir> indexForTheme(const QString &name,
                                     const QStringList &paths,
                                     const QStringList &suffixes);

    static QList<QDir> indexAllThemes(const QString &name,
                                      const QStringList &paths,
                                      const QStringList &filters);

    static void indexTheme(const QString &name, const QStringList &paths,
                           const QStringList &filters, QList<QDir> &result);

    static void indexSubdir(const QDir &dir, const QStringList &filters,
                            QList<QDir> &result);

    static QString _themeName;
    static QStringList _themePaths;
    static QStringList _iconSuffixes;
    static QList<QDir> _searchIndex;
};

#endif // ICONFINDER_H
