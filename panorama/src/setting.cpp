#include "setting.h"

Setting::Setting(QObject *parent) :
    QObject(parent)
{
    connect(_settings, SIGNAL(settingChanged(QString,QString,QVariant,ChangeSource)),
            this, SLOT(handleFieldChange(QString,QString,QVariant)));
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

void Setting::setDefaultValue(const QVariant &value)
{
    if(_default != value)
    {
        _default = value;
        maybeInsertDefault();
        emit defaultValueChanged(_default);
    }
}

void Setting::setValue(const QVariant &value)
{
    if(_settings)
    {
        const QString &section(_section.isEmpty() ? _defaultSection : _section);
        _settings->setSetting(section, _key, value, SettingsHive::External);
    }
}

QVariant Setting::value() const
{
    const QString &section(_section.isEmpty() ? _defaultSection : _section);

    if(_settings)
        return _settings->setting(section, _key);
    else
        return QVariant();
}

void Setting::handleFieldChange(const QString &section, const QString &key,
                                const QVariant &value)
{
    const QString &s(_section.isEmpty() ? _defaultSection : _section);
    if(s == section && _key == key)
        emit valueChanged(value);
}

void Setting::maybeInsertDefault()
{
    const QString &section(_section.isEmpty() ? _defaultSection : _section);

    if(!section.isEmpty() && !_key.isEmpty() && _settings &&
       !_settings->setting(section, _key).isValid() &&
       _default.isValid())
    {
        _settings->setSetting(section, _key, _default, SettingsHive::External);
    }
}

QString Setting::_defaultSection;
SettingsHive *Setting::_settings;

