#include "configuration.h"

Configuration::Configuration(QObject *parent) :
        QObject(parent), _fullscreen(false)
{
    _hive = new SettingsHive(this);

    connect(&_watcher, SIGNAL(fileChanged(QString)),
            this, SLOT(readFile(QString)));
    connect(_hive, SIGNAL(settingChanged(QString,QString,QVariant,ChangeSource)),
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
    bool changed(false);

    //For some reason, the FileWatcher stops tracking files sometimes...
    //(Probably when editors delete+recreate a file instead of modifying it)
    //Thus, we might have to readd it
    if(!_watcher.files().contains(f) && QFileInfo(f).exists())
        _watcher.addPath(f);

    QSettings settings(f, QSettings::IniFormat);

    settings.beginGroup("panorama");
    QString uiDir = settings.value("uiDirectory").toString();
    if(_uiDir != uiDir)
    {
        _uiDir = uiDir;
        changed = true;
    }

    QString ui = settings.value("ui").toString();
    if(_ui != ui)
    {
        _ui = ui;
        changed = true;
    }

    bool fullscreen = settings.value("fullscreen").toBool();
    if(_fullscreen ^ fullscreen)
    {
        _fullscreen = fullscreen;
        changed = true;
    }
    settings.endGroup();

    foreach(const QString &section, settings.childGroups())
    {
        settings.beginGroup(section);
        foreach(const QString &key, settings.allKeys())
        {
            _hive->setSetting(section, key, settings.value(key), SettingsHive::File);
        }
        settings.endGroup();
    }

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
    QSettings out(_file, QSettings::IniFormat);

    out.beginGroup("panorama");
    out.setValue("uiDirectory", _uiDir);
    out.setValue("ui", _ui);
    out.setValue("fullscreen", _fullscreen);
    out.endGroup();

    _hive->writeSettings(out);
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
