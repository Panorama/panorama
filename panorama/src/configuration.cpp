#include "configuration.h"

Configuration::Configuration(QObject *parent) :
    QObject(parent), _fullscreen(false)
{
    _hive = new SettingsHive(this);

    connect(&_watcher, SIGNAL(fileChanged(QString)),
            this, SLOT(readFile(QString)));
    connect(_hive, SIGNAL(settingChanged(QString,QString,QString,ChangeSource)),
            this, SLOT(saveFile()));
}

void Configuration::loadFile(const QString &f)
{
    if(_watcher.files().contains(_file))
        _watcher.removePath(_file);

    _file = f;

    //Try to read the file once
    readFile(f);

    //Only add the file to the watcher if it exists
    if(!_watcher.files().contains(f) && QFileInfo(f).exists())
        _watcher.addPath(f);
}

void Configuration::readFile(const QString &f)
{
    QString line;
    QString section;
    QFile file(f);
    bool changed(false);

    //For some reason, the FileWatcher stops tracking files sometimes...
    //(Probably when editors delete+recreate a file instead of modifying it)
    //Thus, we might have to readd it
    if(!_watcher.files().contains(f) && QFileInfo(f).exists())
        _watcher.addPath(f);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Could not open file " << f;
        return;
    }

    QTextStream in(&file);

    while(!in.atEnd())
    {
        //XXX Optimize this
        line = in.readLine().trimmed();
        if(line.startsWith("#"))
            continue;
        else if(line.startsWith("["))
            section = line.mid(1, line.length() - 2);
        else if(section.isEmpty() && line.startsWith("uiDirectory"))
        {
            QStringList parts = line.split("=");
            if(parts.count() > 1)
            {
                parts.removeFirst();
                line = parts.join("=").trimmed();

                if(line.startsWith("\""))
                    line = line.mid(1, line.length() - 2);

                if(_uiDir != line)
                {
                    _uiDir = line;
                    changed = true;
                }
            }
        }
        else if(section.isEmpty() && line.startsWith("ui"))
        {
            QStringList parts = line.split("=");
            if(parts.count() > 1)
            {
                parts.removeFirst();
                line = parts.join("=").trimmed();

                if(line.startsWith("\""))
                    line = line.mid(1, line.length() - 2);

                if(_ui != line)
                {
                    _ui = line;
                    changed = true;
                }
            }
        }
        else if(section.isEmpty() && line.startsWith("fullscreen"))
        {
            QStringList parts = line.split("=");
            if(parts.count() > 1)
            {
                parts.removeFirst();
                line = parts.join("=").simplified();

                if(line == "\"true\"" && !_fullscreen)
                {
                    changed = true;
                    _fullscreen = true;
                }
                else if(_fullscreen)
                {
                    _fullscreen = false;
                    changed = true;
                }
                else
                {
                    _fullscreen = false;
                }
            }
        }
        else
        {
            QStringList parts = line.split("=");
            if(parts.length() > 1)
            {
                const QString key = parts[0].trimmed();
                parts.removeFirst();
                QString value = parts.join("=").trimmed();

                if(value.startsWith('"'))
                    value = value.mid(1, value.length() - 2);
                _hive->setSetting(section, key, value, SettingsHive::File);
            }
        }
    }
    file.close();

    if(changed)
        emit uiChanged(_uiDir, _ui);
}
void Configuration::reactToChange(const QString&,
                                  const QString&,
                                  const QString&,
                                  SettingsHive::ChangeSource source)
{
    if(source != SettingsHive::File)
        saveFile();
}

void Configuration::saveFile()
{
    QFile file(_file);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Could not open file " << _file;
        return;
    }

    QTextStream out(&file);

    out << "uiDirectory = \"" << _uiDir << '\"' << endl;
    out << "ui = \"" << _ui << '\"' << endl;
    out << "fullscreen = " << (_fullscreen ? "\"true\"" : "\"false\"") << endl;

    _hive->writeIni(out);

    file.flush();
    file.close();
}

QString Configuration::ui() const
{
    return _ui;
}

QString Configuration::uiDir() const
{
    return _uiDir;
}

bool Configuration::fullscreen() const
{
    return _fullscreen;
}

SettingsHive *Configuration::generalConfig() const
{
    return _hive;
}

void Configuration::setUI(const QString &value)
{
    if(_ui != value)
    {
        _ui = value;
        emit uiChanged(_uiDir, _ui);
    }
}

void Configuration::setUIDir(const QString &value)
{
    _uiDir = value;
}

void Configuration::setFullscreen(const bool &value)
{
    _fullscreen = value;
}
