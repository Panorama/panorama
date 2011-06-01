#include "setting.h"

#include "settingshive.h"
#include "configuration.h"
#include <QDebug>

class SettingPrivate
{
    PANORAMA_DECLARE_PUBLIC(Setting)
public:
    void maybeInsertDefault();
    void wire();

    QString section;
    QString key;
    QVariant defaultValue;
};

SettingsSource *_setting_settings = 0;
#define _settings _setting_settings
Configuration *_setting_configuration = 0;
#define _configuration _setting_configuration

Setting::Setting(QObject *parent)
    : QObject(parent)
{
    PANORAMA_INITIALIZE(Setting);
    priv->wire();
}

Setting::~Setting()
{
    PANORAMA_UNINITIALIZE(Setting);
}

Setting::Setting(const QString &section, const QString &key, QObject *parent)
    : QObject(parent)
{
    PANORAMA_INITIALIZE(Setting);
    setSection(section);
    setKey(key);
    priv->wire();
}

Setting::Setting(const QString &section, const QString &key, const QVariant &defaultValue, QObject *parent)
    : QObject(parent)
{
    PANORAMA_INITIALIZE(Setting);
    setSection(section);
    setKey(key);
    setDefaultValue(defaultValue);
    priv->wire();
}

void Setting::setSection(const QString &section)
{
    PANORAMA_PRIVATE(Setting);
    if(priv->section != section)
    {
        priv->section = section;
        priv->maybeInsertDefault();
        emit sectionChanged(section);
    }
}

QString Setting::section() const
{
    PANORAMA_PRIVATE(const Setting);
    return priv->section;
}

void Setting::setKey(const QString &key)
{
    PANORAMA_PRIVATE(Setting);
    if(priv->key != key)
    {
        priv->key = key;
        priv->maybeInsertDefault();
        emit keyChanged(key);
    }
}

QString Setting::key() const
{
    PANORAMA_PRIVATE(const Setting);
    return priv->key;
}

void Setting::setDefaultValue(const QVariant &defaultValue)
{
    PANORAMA_PRIVATE(Setting);
    if(priv->defaultValue != defaultValue)
    {
        priv->defaultValue = defaultValue;
        priv->maybeInsertDefault();
        emit defaultValueChanged(defaultValue);
    }
}

QVariant Setting::defaultValue() const
{
    PANORAMA_PRIVATE(const Setting);
    return priv->defaultValue;
}

void Setting::setValue(const QVariant &value)
{
    PANORAMA_PRIVATE(Setting);
    if(_settings)
    {
        _settings->setSetting(priv->section, priv->key, value, SettingsSource::External);
    }
}

QVariant Setting::value() const
{
    QVariant result;
    PANORAMA_PRIVATE(const Setting);
    if(_settings)
        result = _settings->setting(priv->section, priv->key);
    return result;
}

void Setting::handleFieldChange(const QString &section, const QString &key,
                                const QVariant &value)
{
    PANORAMA_PRIVATE(Setting);
    if(priv->section == section && priv->key == key)
        emit valueChanged(value);
}

void SettingPrivate::maybeInsertDefault()
{
    if(!section.isEmpty() && !key.isEmpty() && _settings &&
       !_settings->setting(section, key).isValid() &&
       defaultValue.isValid())
    {
        _settings->setSetting(section, key, defaultValue, SettingsSource::External);
    }
}

void SettingPrivate::wire()
{
    PANORAMA_PUBLIC(Setting);
    if(!_settings) {
        _configuration = new Configuration();
        _settings = _configuration->generalConfig();
        pub->connect(_settings, SIGNAL(settingChanged(QString,QString,QVariant,SettingsSource::ChangeSource)),
                     pub, SLOT(handleFieldChange(QString,QString,QVariant)));
        _configuration->loadConfiguration();
    } else {
        pub->connect(_settings, SIGNAL(settingChanged(QString,QString,QVariant,SettingsSource::ChangeSource)),
                     pub, SLOT(handleFieldChange(QString,QString,QVariant)));
    }
}
