#include "settingshive.h"
#include <QStringList>
#include <QDebug>

SettingsHive::SettingsHive(QObject *parent) :
        SettingsSource(parent)
{
    _store = new QHash<QString, QHash<QString, QVariant> *>;
}

SettingsHive::~SettingsHive()
{
    foreach(const QString &key, _store->keys())
        delete _store->value(key);
    delete _store;
}

void SettingsHive::writeSettings(QSettings &out) const
{
    foreach(const QString &section, _store->keys())
    {
        foreach(const QString &key, _store->value(section)->keys())
        {
            const QVariant value =  _store->value(section)->value(key);
            const QString actualKey = QString(section).append("/").append(key);
            if(value.isValid())
                out.setValue(actualKey, value);
            else
                out.remove(actualKey);
        }
    }
}

void SettingsHive::readSettings(const QSettings &in)
{
    foreach(const QString &key, in.allKeys())
    {
        const int slash = key.indexOf('/');
        const QString section = key.left(slash);
        const QString sectionKey = key.right(key.length() - slash - 1);
        setSetting(section, sectionKey, in.value(key), SettingsSource::File);
    }
}

QVariant SettingsHive::setting(const QString &section, const QString &key) const
{
    if(_store && _store->contains(section) &&
       _store->value(section)->contains(key))
        return _store->value(section)->value(key);
    else
        return QVariant();
}

void SettingsHive::setSetting(const QString &section, const QString &key,
                              const QVariant &value,
                              SettingsHive::ChangeSource source)
{
    if(_store)
    {
        if(!_store->contains(section))
            _store->insert(section, new QHash<QString, QVariant>);

        if(_store->value(section)->value(key) != value)
        {
            _store->value(section)->insert(key, value);
            emit settingChanged(section, key, value, source);
        }
    }
}
