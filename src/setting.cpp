#include "setting.h"

Setting::Setting(QObject *parent) :
    QObject(parent)
{
    connect(_settings, SIGNAL(settingChanged(QString,QString,QString)),
            this, SLOT(handleFieldChange(QString,QString,QString)));
}

void Setting::setSettingsSource(SettingsHive *value)
{
    _settings = value;
}

void Setting::setSection(const QString &section)
{
    if(_section != section)
    {
        _section = section;
        maybeInsertDefault();
        emit sectionChanged(section);
    }
}

void Setting::setKey(const QString &key)
{
    if(_key != key)
    {
        _key = key;
        maybeInsertDefault();
        emit keyChanged(key);
    }
}

void Setting::setDefaultValue(const QString &value)
{
    if(_default != value)
    {
        _default = value;
        maybeInsertDefault();
        emit defaultValueChanged(_default);
    }
}

void Setting::setValue(const QString &value)
{
    if(_settings)
    {
        const QString &section(_section.isEmpty() ? _defaultSection : _section);
        _settings->setSetting(section, _key, value);
    }
}

QString Setting::value() const
{
    const QString &section(_section.isEmpty() ? _defaultSection : _section);

    if(_settings)
        return _settings->setting(section, _key);
    else
        return QString();
}

void Setting::handleFieldChange(const QString &section, const QString &key,
                                const QString &value)
{
    const QString &s(_section.isEmpty() ? _defaultSection : _section);
    if(s == section && _key == key)
        emit valueChanged(value);
}

void Setting::maybeInsertDefault()
{
    const QString &section(_section.isEmpty() ? _defaultSection : _section);

    if(!section.isEmpty() && !_key.isEmpty() && _settings &&
       _settings->setting(section, _key).length() == 0 &&
       _default.length() != 0)
    {
        _settings->setSetting(section, _key, _default);
    }
}

QString Setting::_defaultSection;
SettingsHive *Setting::_settings;

QML_DEFINE_TYPE(Panorama,1,0,Setting,Setting);
