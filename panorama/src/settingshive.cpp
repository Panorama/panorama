#include "settingshive.h"

SettingsHive::SettingsHive(QObject *parent) :
    QObject(parent)
{
    _store = new QHash<QString, QHash<QString, QString> *>;
}

SettingsHive::~SettingsHive()
{
    foreach(const QString &key, _store->keys())
        delete _store->value(key);
    delete _store;
}

void SettingsHive::writeIni(QTextStream &out) const
{
    foreach(const QString &section, _store->keys())
    {
        out << endl << "[" << section << "]" << endl;
        foreach(const QString &key, _store->value(section)->keys())
        {
            out << key << " = \""
                    << QString(_store->value(section)->value(key))
                        .replace('\n', ' ')
                    << '\"' << endl;
        }
    }
}

QString SettingsHive::setting(const QString &section, const QString &key) const
{
    if(_store && _store->contains(section) &&
       _store->value(section)->contains(key))
        return _store->value(section)->value(key);
    else
        return QString();
}

void SettingsHive::setSetting(const QString &section, const QString &key,
                              const QString &value,
                              SettingsHive::ChangeSource source)
{
    if(_store)
    {
        if(!_store->contains(section))
            _store->insert(section, new QHash<QString, QString>);

        if(_store->value(section)->value(key) != value)
        {
            _store->value(section)->insert(key, value);
            emit settingChanged(section, key, value, source);
        }
    }
}
