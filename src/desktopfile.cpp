#include "desktopfile.h"

DesktopFile::DesktopFile(const QString &file)
{
    _file = file;
}

Application DesktopFile::readToApplication()
{
    Application result;
    QString line;
    QString enName, enComment;
    QString genericName, genericComment;
    QFile file(_file);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Could not open file " << _file;
        return result;
    }

    QTextStream in(&file);

    //Skip ahead over the "[Desktop Entry]" section
    while(!in.atEnd() && !in.readLine().contains("[Desktop Entry]"));

    while(!in.atEnd())
    {
        line = in.readLine();

        //User comment (Hah! A meta-pun!)
        if(line.startsWith("#"))
            continue;
        //Name
        else if(line.startsWith(NAME_FIELD))
            readLocalizedWithFallbacks(line, NAME_FIELD, result.name, enName,
                                       genericName);
        //Comment
        else if(line.startsWith(COMMENT_FIELD))
            readLocalizedWithFallbacks(line, COMMENT_FIELD, result.comment,
                                       enComment, genericComment);
        //Exec
        else if(line.startsWith(EXEC_FIELD))
            result.id = readField(line, EXEC_FIELD); //Temporarily hold inside of id
        //Icon
        else if(line.startsWith(ICON_FIELD))
            result.icon = IconFinder::findIcon(readField(line, ICON_FIELD));
        //X-Desktop-File-Install-Version
        else if(line.startsWith(VERSION_FIELD))
            result.version = readField(line, VERSION_FIELD);
        //X-Pandora-UID
        else if(line.startsWith(PANDORA_UID_FIELD))
            result.pandoraId = readField(line, PANDORA_UID_FIELD);
        //Categories
        else if(line.startsWith(CATEGORIES_FIELD))
        {
            const QString data = readField(line, CATEGORIES_FIELD);
            if(data.length() > 0)
            {
                result.categories = data.split(";");
                for(int i = 0; i < result.categories.count(); i++)
                {
                    result.categories[i] = result.categories[i].trimmed();
                }
            }
        }
        //Type
        //(We don't want to load this application if its Type isn't Application)
        else if(line.startsWith(TYPES_FIELD) && !line.contains(APPLICATION_TYPE))
        {
            file.close();
            return Application();
        }
        //Hidden
        //(We don't want to add the file if it's supposed to be hidden)
        else if(line.startsWith("Hidden=true"))
        {
            file.close();
            return Application();
        }
        //NoDisplay
        //(Dito)
        else if(line.startsWith("NoDisplay=true"))
        {
            file.close();
            return Application();
        }
        //We stop if we reach a new section
        else if(line.startsWith("["))
            break;
    }
    file.close();

    //Merge in the fields from the fallback localization
    if(result.name.isEmpty())
    {
        if(enName.isEmpty())
            result.name = genericName;
        else
            result.name = enName;
    }

    if(result.comment.isEmpty())
    {
        if(enComment.isEmpty())
            result.comment = genericComment;
        else
            result.comment = enComment;
    }

    if(!result.pandoraId.isEmpty())
    {
        Pnd pnd(PndScanner::pndForUID(result.pandoraId));
        result.clockspeed = pnd.clockspeed;
        result.preview = pnd.preview;
    }

    result.relatedFile = _file;
    return result;
}

void DesktopFile::readLocalizedWithFallbacks(const QString &line, const QString &fieldName,
                                             QString &local, QString &en, QString &generic)
{
    //XXX This could be done much more efficiently
    QString tmp;
    int i = -1;

    //We have 6 levels of localization, in 3 groups:
    //Native:
    //0: ideal translation
    //1: language-generic translation
    //English:
    //2: english translation
    //3: american english translation
    //4: brittish translation
    //Generic:
    //5: whatever unlocalized translation happens to be last in the file
    do {
        i++;
        switch(i)
        {
        case 0:
            tmp = QLocale::system().name();
            break;
        case 1:
            tmp = QLocale::system().name().split("_")[0];
            break;
        case 2:
            tmp = "en";
            break;
        case 3:
            tmp = "en_US";
            break;
        case 4:
            tmp = "en_GB";
            break;
        }

        if(i == 5)
            tmp = readField(line, fieldName);
        else
            tmp = readField(line, FIELD_TEMPLATE.arg(fieldName).arg(tmp));
    } while(tmp.isEmpty() && i < 6);

    switch(i)
    {
    case 0:
    case 1:
        local = tmp;
        break;
    case 2:
    case 3:
    case 4:
        en = tmp;
        break;
    case 5:
        generic = tmp;
    }
}

QString DesktopFile::readField(const QString &line, const QString &field) const
{
    QString start(field);
    start.append("=");
    if(line.startsWith(start))
    {
        //Don't do 'split("=")' here; it's against the standard and leads to bugs elsewhere
        return line.right(line.length() - field.length() -1).split("#")[0].trimmed();
    }
    else
        return QString();
}

const QString DesktopFile::NAME_FIELD       = QString("Name");
const QString DesktopFile::COMMENT_FIELD    = QString("Comment");
const QString DesktopFile::EXEC_FIELD       = QString("Exec");
const QString DesktopFile::ICON_FIELD       = QString("Icon");
const QString DesktopFile::VERSION_FIELD    = QString("X-Desktop-File-Install-Version");
const QString DesktopFile::PANDORA_UID_FIELD= QString("X-Pandora-UID");
const QString DesktopFile::CATEGORIES_FIELD = QString("Categories");
const QString DesktopFile::TYPES_FIELD      = QString("Type");
const QString DesktopFile::APPLICATION_TYPE = QString("Application");
const QString DesktopFile::FIELD_TEMPLATE   = QString("%1[%2]");
