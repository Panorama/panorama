#include "configuration.h"

Configuration::Configuration(QObject *parent) :
        QObject(parent)
{
    _hive = new SettingsHive(this);
    _settings = 0;

    connect(&_watcher, SIGNAL(fileChanged(QString)),
            this, SLOT(loadConfiguration()));
    connect(_hive, SIGNAL(settingChanged(QString,QString,QVariant,SettingsSource::ChangeSource)),
            this, SLOT(reactToChange(QString,QString,QVariant,SettingsSource::ChangeSource)));
}

void Configuration::loadConfiguration()
{
    initConfiguration();
    _settings->sync();

    if(QFileInfo(_settings->fileName()).exists() && !_watcher.files().contains(_settings->fileName()))
        _watcher.addPath(_settings->fileName());

    foreach(const QString &section, _settings->childGroups())
    {
        _settings->beginGroup(section);
        foreach(const QString &key, _settings->allKeys())
        {
            _hive->setSetting(section, key, _settings->value(key), SettingsSource::File);
        }
        _settings->endGroup();
    }
}

void Configuration::saveConfiguration()
{
    initConfiguration();
    _hive->writeSettings(*_settings);
    _settings->sync();
}

void Configuration::reactToChange(const QString&,
                                  const QString&,
                                  const QVariant&,
                                  SettingsSource::ChangeSource source)
{
    if(source != SettingsSource::File)
        saveConfiguration();
}

SettingsHive *Configuration::generalConfig() const
{
    return _hive;
}

void Configuration::initConfiguration()
{
    if(!_settings) {
#ifdef PANDORA
        _settings = new QSettings(CONFIG_FILE, QSettings::IniFormat, this);
#else
        _settings = new QSettings(QSettings::UserScope, "panorama", "core", this);
#endif
        if(_settings->allKeys().isEmpty()) {
            qWarning() << "Warning: No configuration file detected, creating default configuration.";
            _settings->beginGroup("panorama");
            {
                _settings->setValue("uiDirectory", "interfaces");
                _settings->setValue("ui", "Test");
                _settings->setValue("fullscreen", false);
            }
            _settings->endGroup();
            _settings->beginGroup("system");
            {
                _settings->setValue("clockspeed", 600);
                _settings->setValue("favorites", "");
            }
            _settings->endGroup();
            _settings->sync();
        }
        _watcher.addPath(_settings->fileName());
        qDebug() << "Settings are saved in" << _settings->fileName();
    }
}
