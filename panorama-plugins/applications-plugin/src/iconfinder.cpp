#include "iconfinder.h"

#include <QtCore/QList>
#include <QtCore/QHash>
#include <QtCore/QDir>
#include <QtCore/QString>
#include <QtCore/QLibrary>
#include <QtCore/QSettings>
#include <QtCore/QTextStream>

#ifdef Q_WS_X11
class QIconTheme
{
public:
    QIconTheme(QHash<int, QString> dirList, QStringList parents)
        : _dirList(dirList), _parents(parents), _valid(true) {}
    QIconTheme() : _valid(false) {}
    const QHash<int, QString> &dirList() const { return _dirList; }
    const QStringList &parents() const { return _parents; }
    bool isValid() const { return _valid; }
private:
    QHash<int, QString> _dirList;
    QStringList _parents;
    bool _valid;
};

class QtIconLoaderImplementation
{
public:
    QtIconLoaderImplementation();
    QString findIcon(int size, const QString &name) const;

private:
    QIconTheme parseIndexFile(const QString &themeName) const;
    void lookupIconTheme() const;
    QString findIconHelper(int size,
                           const QString &themeName,
                           const QString &iconName,
                           QStringList &visited) const;
    mutable QString themeName;
    mutable QStringList iconDirs;
    mutable QHash <QString, QIconTheme> themeList;
};

Q_GLOBAL_STATIC(QtIconLoaderImplementation, iconLoaderInstance);
#endif

QString IconFinder::findIcon(const QString &name, const QString &fallback)
{
    QString icon;

    if(name.contains(QDir::separator()))
        return name; //Already resolved

#ifdef Q_WS_X11
    QString png = QLatin1String(".png");
    QList<int> iconSizes;
    iconSizes << 64 << 48 << 32 << 24 << 16;
    foreach(int size, iconSizes)
    {
        icon = iconLoaderInstance()->findIcon(size, name + png);
        if(!icon.isNull())
            return icon;
    }
#endif
    Q_UNUSED(name);
    return fallback;
}

#ifdef Q_WS_X11
QtIconLoaderImplementation::QtIconLoaderImplementation()
{
    lookupIconTheme();
}

extern "C" {
    struct GConfClient;
    struct GError;
    typedef void (*Ptr_g_type_init)();
    typedef GConfClient* (*Ptr_gconf_client_get_default)();
    typedef char* (*Ptr_gconf_client_get_string)(GConfClient*, const char*, GError **);
    typedef void (*Ptr_g_object_unref)(void *);
    typedef void (*Ptr_g_error_free)(GError *);
    typedef void (*Ptr_g_free)(void*);
    static Ptr_g_type_init p_g_type_init = 0;
    static Ptr_gconf_client_get_default p_gconf_client_get_default = 0;
    static Ptr_gconf_client_get_string p_gconf_client_get_string = 0;
    static Ptr_g_object_unref p_g_object_unref = 0;
    static Ptr_g_error_free p_g_error_free = 0;
    static Ptr_g_free p_g_free = 0;
}

static int kdeVersion()
{
    static int version = qgetenv("KDE_SESSION_VERSION").toInt();
    return version;
}

static QString kdeHome()
{
    static QString kdeHomePath;
    if (kdeHomePath.isEmpty()) {
        kdeHomePath = QFile::decodeName(qgetenv("KDEHOME"));
        if (kdeHomePath.isEmpty()) {
            int kdeSessionVersion = kdeVersion();
            QDir homeDir(QDir::homePath());
            QString kdeConfDir(QLatin1String("/.kde"));
            if (4 == kdeSessionVersion && homeDir.exists(QLatin1String(".kde4")))
                kdeConfDir = QLatin1String("/.kde4");
            kdeHomePath = QDir::homePath() + kdeConfDir;
        }
    }
    return kdeHomePath;
}

void QtIconLoaderImplementation::lookupIconTheme() const
{

#ifdef Q_WS_X11
    QString dataDirs = QFile::decodeName(getenv("XDG_DATA_DIRS"));
    if (dataDirs.isEmpty())
        dataDirs = QLatin1String("/usr/local/share:/usr/share");

    dataDirs.prepend(QDir::homePath() + QLatin1String("/:"));
    iconDirs = dataDirs.split(QLatin1Char(':'));

    if (qgetenv("DESKTOP_SESSION") == "gnome" ||
        !qgetenv("GNOME_DESKTOP_SESSION_ID").isEmpty()) {

        if (themeName.isEmpty()) {
            p_g_type_init =              (Ptr_g_type_init)QLibrary::resolve(QLatin1String("gobject-2.0"), 0, "g_type_init");
            p_gconf_client_get_default = (Ptr_gconf_client_get_default)QLibrary::resolve(QLatin1String("gconf-2"), 4, "gconf_client_get_default");
            p_gconf_client_get_string =  (Ptr_gconf_client_get_string)QLibrary::resolve(QLatin1String("gconf-2"), 4, "gconf_client_get_string");
            p_g_object_unref =           (Ptr_g_object_unref)QLibrary::resolve(QLatin1String("gobject-2.0"), 0, "g_object_unref");
            p_g_error_free =             (Ptr_g_error_free)QLibrary::resolve(QLatin1String("glib-2.0"), 0, "g_error_free");
            p_g_free =                   (Ptr_g_free)QLibrary::resolve(QLatin1String("glib-2.0"), 0, "g_free");

            if (p_g_type_init && p_gconf_client_get_default &&
                p_gconf_client_get_string && p_g_object_unref &&
                p_g_error_free && p_g_free) {

                p_g_type_init();
                GConfClient* client = p_gconf_client_get_default();
                GError *err = 0;

                char *str = p_gconf_client_get_string(client, "/desktop/gnome/interface/icon_theme", &err);
                if (!err) {
                    themeName = QString::fromUtf8(str);
                    p_g_free(str);
                }

                p_g_object_unref(client);
                if (err)
                    p_g_error_free (err);
            }
            if (themeName.isEmpty())
                themeName = QLatin1String("gnome");
        }

        if (!themeName.isEmpty())
            return;
    }

    if (dataDirs.isEmpty())
        dataDirs = QLatin1String("/usr/local/share:/usr/share");

    dataDirs += QLatin1Char(':') + kdeHome() + QLatin1String("/share");
    dataDirs.prepend(QDir::homePath() + QLatin1String("/:"));
    QStringList kdeDirs = QFile::decodeName(getenv("KDEDIRS")).split(QLatin1Char(':'));
    Q_FOREACH (const QString dirName, kdeDirs)
            dataDirs.append(QLatin1Char(':') + dirName + QLatin1String("/share"));
    iconDirs = dataDirs.split(QLatin1Char(':'));

    QFileInfo fileInfo(QLatin1String("/usr/share/icons/default.kde"));
    QDir dir(fileInfo.canonicalFilePath());
    QString kdeDefault = kdeVersion() >= 4 ? QString::fromLatin1("oxygen") : QString::fromLatin1("crystalsvg");
    QString defaultTheme = fileInfo.exists() ? dir.dirName() : kdeDefault;
    QSettings settings(kdeHome() + QLatin1String("/share/config/kdeglobals"), QSettings::IniFormat);
    settings.beginGroup(QLatin1String("Icons"));
    themeName = settings.value(QLatin1String("Theme"), defaultTheme).toString();
#endif
}

QIconTheme QtIconLoaderImplementation::parseIndexFile(const QString &themeName) const
{
    QIconTheme theme;
    QFile themeIndex;
    QStringList parents;
    QHash <int, QString> dirList;

    for ( int i = 0 ; i < iconDirs.size() && !themeIndex.exists() ; ++i) {
        const QString &contentDir = QLatin1String(iconDirs[i].startsWith(QDir::homePath()) ? "/.icons/" : "/icons/");
        themeIndex.setFileName(iconDirs[i] + contentDir + themeName + QLatin1String("/index.theme"));
    }

    if (themeIndex.exists()) {
        QSettings indexReader(themeIndex.fileName(), QSettings::IniFormat);
        Q_FOREACH (const QString &key, indexReader.allKeys()) {
            if (key.endsWith("/Size")) {
                if (int size = indexReader.value(key).toInt())
                    dirList.insertMulti(size, key.left(key.size() - 5));
            }
        }

        parents = indexReader.value(QLatin1String("Icon Theme/Inherits")).toStringList();
    }

    if (kdeVersion() >= 3) {
        QFileInfo fileInfo(QLatin1String("/usr/share/icons/default.kde"));
        QDir dir(fileInfo.canonicalFilePath());
        QString defaultKDETheme = dir.exists() ? dir.dirName() : kdeVersion() == 3 ?
                                  QString::fromLatin1("crystalsvg") : QString::fromLatin1("oxygen");
        if (!parents.contains(defaultKDETheme) && themeName != defaultKDETheme)
            parents.append(defaultKDETheme);
    } else if (parents.isEmpty() && themeName != QLatin1String("hicolor")) {
        parents.append(QLatin1String("hicolor"));
    }

    theme = QIconTheme(dirList, parents);
    return theme;
}

QString QtIconLoaderImplementation::findIconHelper(int size, const QString &themeName,
                                                   const QString &iconName, QStringList &visited) const
{
    QString result;

    if (!themeName.isEmpty()) {
        visited << themeName;
        QIconTheme theme = themeList.value(themeName);

        if (!theme.isValid()) {
            theme = parseIndexFile(themeName);
            themeList.insert(themeName, theme);
        }

        if (!theme.isValid())
            return QString();

        QList <QString> subDirs = theme.dirList().values(size);

        for ( int i = 0 ; i < iconDirs.size() ; ++i) {
            for ( int j = 0 ; j < subDirs.size() ; ++j) {
                QString contentDir = (iconDirs[i].startsWith(QDir::homePath())) ?
                                     QLatin1String("/.icons/") : QLatin1String("/icons/");
                QString fileName = iconDirs[i] + contentDir + themeName + QLatin1Char('/') + subDirs[j] + QLatin1Char('/') + iconName;
                QFile file(fileName);
                if (file.exists())
                    result = fileName;
                if (!result.isNull())
                    break;
            }
        }

        if (result.isNull()) {
            QStringList parents = theme.parents();
            //search recursively through inherited themes
            for (int i = 0 ; result.isNull() && i < parents.size() ; ++i) {
                QString parentTheme = parents[i].trimmed();
                if (!visited.contains(parentTheme)) //guard against endless recursion
                    result = findIconHelper(size, parentTheme, iconName, visited);
            }
        }
    }
    return result;
}

QString QtIconLoaderImplementation::findIcon(int size, const QString &name) const
{
    QString result;

    if (!themeName.isEmpty()) {
        QStringList visited;
        result = findIconHelper(size, themeName, name, visited);
    }
    return result;
}
#endif
