#include "desktopfile.h"
#include <QCryptographicHash>
#include <QTemporaryFile>
#include <QResource>

class DesktopFilePrivate
{
    PANORAMA_DECLARE_PUBLIC(DesktopFile)
public:
    QString readLocalized(const QMap<QString, QVariant> &map, const QString &fieldName) const;
    QMap<QString, QVariant> parseDesktop(const QString &file) const;

    QString file;
};

DesktopFile::DesktopFile(const QString &file)
{
    PANORAMA_INITIALIZE(DesktopFile);
    priv->file = file;
}

DesktopFile::~DesktopFile()
{
    PANORAMA_UNINITIALIZE(DesktopFile);
}

Application DesktopFile::readToApplication()
{
    PANORAMA_PRIVATE(DesktopFile);
    Application result;
    result.clockspeed = 0;

    const QMap<QString, QVariant> entries = priv->parseDesktop(priv->file);

    //Should we not load this?
    if(!entries["Type"].toString().contains("Application") || //Not an app
       entries["Hidden"].toBool() || //Should be hidden in menus
       entries["NoDisplay"].toBool()) //Should not be displayed
    {
        return Application();
    }

    result.name = priv->readLocalized(entries, "Name");
    result.comment = priv->readLocalized(entries, "Comment");

    result.exec = entries["Exec"].toString();
    result.icon = IconFinder::findIcon(entries["Icon"].toString());
    result.version = entries["X-Desktop-File-Install-Version"].toString();
    result.pandoraId = entries["X-Pandora-UID"].toString();

    const QString categoriesString = entries["Categories"].toString();
    if(!categoriesString.isNull() && !categoriesString.isEmpty())
    {
        result.categories = categoriesString.split(";");
        for(int i = 0; i < result.categories.count(); i++)
        {
            result.categories[i] = result.categories[i].trimmed();
        }
    }

    //Is this a PND app? Then load additional metadata from libpnd
    if(!result.pandoraId.isEmpty())
    {
        Pnd pnd(PndScanner::pndForUID(result.pandoraId));
        result.clockspeed = pnd.clockspeed;
        result.preview = pnd.preview;
    }

    result.relatedFile = priv->file;

    result.id = QCryptographicHash::hash(result.exec.toUtf8(), QCryptographicHash::Sha1).toHex();

    return result;
}

QString DesktopFilePrivate::readLocalized(const QMap<QString, QVariant> &entries, const QString &fieldName) const
{
    /* We have 6 levels of localization, in 3 groups:
       Native:
         0: ideal translation
         1: language-generic translation
       English:
         2: english translation
         3: american english translation
         4: brittish translation
       Generic:
         5: whatever unlocalized translation happens to be in the file
    */
    for(int i = 0; i < 5; i++) {
        QString locale;
        switch(i)
        {
        case 0:
            locale = QLocale::system().name();
            break;
        case 1:
            locale = QLocale::system().name().split("_")[0];
            break;
        case 2:
            locale = "en";
            break;
        case 3:
            locale = "en_US";
            break;
        case 4:
            locale = "en_GB";
            break;
        }

        QString result = entries[QString("%1[%2]").arg(fieldName).arg(locale)].toString();
        if(!result.isNull())
            return result;
    }
    return entries[fieldName].toString();
}

QMap<QString, QVariant> DesktopFilePrivate::parseDesktop(const QString &file) const
{
    QString line;
    bool inDesktopEntry = false;
    QMap<QString, QVariant> result;

    QFile f(file);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&f);

    while(!stream.atEnd())
    {
        line = stream.readLine().trimmed();
        if(line.startsWith(';') || line.startsWith('#'))
            continue;
        else if(line.startsWith('['))
            inDesktopEntry = (line.mid(1, line.indexOf(']') - 1) == QLatin1String("Desktop Entry"));
        else if(inDesktopEntry)
        {
            const int eq = line.indexOf('=');
            result[line.left(eq).trimmed()] = QVariant(line.right(line.length() - eq - 1).trimmed());
        }
    }
    f.close();

    return result;
}
