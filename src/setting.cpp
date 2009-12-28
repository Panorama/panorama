#include "setting.h"

Setting::Setting(QObject *parent) :
    QObject(parent)
{
    connect(&_prop, SIGNAL(fieldChanged(QString,QString,QString)), this, SLOT(handleFieldChange(QString,QString,QString)));
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
        QString section(_section.isEmpty() ? _defaultSection : _section);
        section.replace('\n', ' ');
        QString key(_key);
        key.replace('\n', ' ');

        if(!_settings->contains(section))
            _settings->insert(section, new QHash<QString, QString>);

        if(_settings->value(section)->value(key) != value)
        {
            _settings->value(section)->insert(key, value);
            _prop.changeField(_section, _key, value);
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

void Setting::handleFieldChange(const QString &section, const QString &key, const QString &value)
{
    if(_section == section && _key == key)
        emit valueChanged(value);
}

void Setting::maybeInsertDefault()
{
    QString section(_section.isEmpty() ? _defaultSection : _section);
    if(section.isEmpty())
        return;
    section.replace('\n', ' ');

    QString key(_key);
    if(key.isEmpty())
        return;
    key.replace('\n', ' ');

    if(!_settings->contains(section))
        _settings->insert(section, new QHash<QString, QString>);

    if(_settings && !_settings->value(section)->contains(key))
    {
        _settings->value(section)->insert(key, _default);
        _prop.changeField(_section, _key, _default);
    }
}

PrivatePropagator::PrivatePropagator(QObject *parent) :
   QObject(parent)
{}

void PrivatePropagator::changeField(const QString &section, const QString &key, const QString &value)
{
    emit fieldChanged(section, key, value);
}

PrivatePropagator Setting::_prop;
QString Setting::_defaultSection;
QHash<QString, QHash<QString, QString> *> *Setting::_settings;

QML_DEFINE_TYPE(Panorama,1,0,Setting,Setting)
