#include "setting.h"

Setting::Setting(QObject *parent) :
    QObject(parent)
{
}

void Setting::setSettingsSource(QHash<QString, QHash<QString, QString> *> *value)
{
    _settings = value;
}

void Setting::setSection(const QString &section)
{
    if(_section != section)
    {
        _section = section;
        emit sectionChanged(section);
    }
}

void Setting::setKey(const QString &key)
{
    if(_key != key)
    {
        _key = key;
        emit keyChanged(key);
    }
}

void Setting::setValue(const QString &value)
{
    if(_settings)
    {
        QString section(_section.isEmpty() ? _defaultSection : _section);
        section.replace('\n', ' ');
        QString key(_key);
        key.replace('\n', ' ');

        if(!_settings->contains(section))
            _settings->insert(section, new QHash<QString, QString>);

        if(_settings->value(section)->value(key) != value)
        {
            _settings->value(section)->insert(key, value);
            emit valueChanged(value);
        }
    }
}

QString Setting::value() const
{
    QString section(_section.isEmpty() ? _defaultSection : _section);
    section.replace('\n', ' ');
    QString key(_key);
    key.replace('\n', ' ');

    if(_settings && _settings->contains(section) && _settings->value(section)->contains(key))
        return _settings->value(section)->value(key);
    else
        return QString();
}

QString Setting::_defaultSection;
QHash<QString, QHash<QString, QString> *> *Setting::_settings;

QML_DEFINE_TYPE(Panorama,1,0,Setting,Setting)
