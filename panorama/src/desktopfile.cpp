#include "desktopfile.h"
#include <QCryptographicHash>
#include <QTemporaryFile>
#include <QResource>

// TODO Fix constants, there's lots of memory duplication here

DesktopFile::DesktopFile(const QString &file)
{
    _file = file;
}

Application DesktopFile::readToApplication()
{
    Application result;
    result.clockspeed = 0;

    const QMap<QString, QVariant> entries = parseDesktop(_file);

    //Should we not load this?
    if(!entries[TYPES_FIELD].toString().contains(APPLICATION_TYPE) || //Not an app
       entries["Hidden"].toBool() || //Should be hidden in menus
       entries["NoDisplay"].toBool()) //Should not be displayed
    {
        return Application();
    }

    //Name
    result.name = readLocalized(entries, NAME_FIELD);

    //Comment
    result.comment = readLocalized(entries, COMMENT_FIELD);

    //Exec
    result.exec = entries[EXEC_FIELD].toString();

    //Icon
    result.icon = IconFinder::findIcon(entries[ICON_FIELD].toString());

    //X-Desktop-File-Install-Version
    result.version = entries[VERSION_FIELD].toString();

    //X-Pandora-UID
    result.pandoraId = entries[PANDORA_UID_FIELD].toString();

    //Categories
    const QString categoriesString = entries[CATEGORIES_FIELD].toString();
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

    result.relatedFile = _file;

    result.id = QCryptographicHash::hash(result.exec.toUtf8(), QCryptographicHash::Sha1).toHex();

    return result;
}

QString DesktopFile::readLocalized(const QMap<QString, QVariant> &entries, const QString &fieldName)
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

        QString result = entries[FIELD_TEMPLATE.arg(fieldName).arg(locale)].toString();
        if(!result.isNull())
            return result;
    }
    return entries[fieldName].toString();
}

QMap<QString, QVariant> DesktopFile::parseDesktop(const QString &file)
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

const QString DesktopFile::NAME_FIELD       = QString("Name");
const QString DesktopFile::COMMENT_FIELD    = QString("Comment");
const QString DesktopFile::EXEC_FIELD       = QString("Exec");
const QString DesktopFile::ICON_FIELD       = QString("Icon");
const QString DesktopFile::VERSION_FIELD    =
        QString("X-Desktop-File-Install-Version");
const QString DesktopFile::PANDORA_UID_FIELD= QString("X-Pandora-UID");
const QString DesktopFile::CATEGORIES_FIELD = QString("Categories");
const QString DesktopFile::TYPES_FIELD      = QString("Type");
const QString DesktopFile::APPLICATION_TYPE = QString("Application");
const QString DesktopFile::FIELD_TEMPLATE   = QString("%1[%2]");
