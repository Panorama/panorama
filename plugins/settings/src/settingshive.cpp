#include "settingshive.h"

#include <QStringList>

class SettingsHivePrivate
{
    PANORAMA_DECLARE_PUBLIC(SettingsHive)
public:
    explicit SettingsHivePrivate();
    ~SettingsHivePrivate();
    QHash<QString, QHash<QString, QVariant> *> *store;
};

SettingsHive::SettingsHive(QObject *parent)
    : SettingsSource(parent)
{
    PANORAMA_INITIALIZE(SettingsHive);
}

SettingsHive::SettingsHive(const QSettings &in, QObject *parent)
    : SettingsSource(parent)
{
    PANORAMA_INITIALIZE(SettingsHive);
    readSettings(in);
}

SettingsHive::~SettingsHive()
{
    PANORAMA_UNINITIALIZE(SettingsHive);
}

void SettingsHive::writeSettings(QSettings &out) const
{
    PANORAMA_PRIVATE(const SettingsHive);
    foreach(const QString &section, priv->store->keys())
    {
        foreach(const QString &key, priv->store->value(section)->keys())
        {
            const QVariant value =  priv->store->value(section)->value(key);
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
        static const QRegExp boolean("(true|false)\\b");
        static const QRegExp integer("[+-]?\\b\\d+\\b");
        static const QRegExp real("((\\b[0-9]+)?\\.)?\\b[0-9]+([eE][-+]?[0-9]+)?\\b");

        const QVariant value = in.value(key);
        QVariant result(value);

        if(boolean.exactMatch(value.toString()))
            result = QVariant(result.toBool());
        else if(integer.exactMatch(value.toString()))
            result = QVariant(result.toInt());
        else if(real.exactMatch(value.toString()))
            result = QVariant(result.toDouble());

        setSetting(section, sectionKey, result, SettingsSource::File);
    }
}

QVariant SettingsHive::setting(const QString &section, const QString &key) const
{
    PANORAMA_PRIVATE(const SettingsHive);
    if(priv->store && priv->store->contains(section) &&
       priv->store->value(section)->contains(key))
        return priv->store->value(section)->value(key);
    else
        return QVariant();
}

void SettingsHive::setSetting(const QString &section, const QString &key,
                              const QVariant &value,
                              SettingsHive::ChangeSource source)
{
    PANORAMA_PRIVATE(const SettingsHive);
    if(priv->store)
    {
        if(!priv->store->contains(section))
            priv->store->insert(section, new QHash<QString, QVariant>);

        if(priv->store->value(section)->value(key) != value)
        {
            priv->store->value(section)->insert(key, value);
            emit settingChanged(section, key, value, source);
        }
    }
}

SettingsHivePrivate::SettingsHivePrivate()
{
    store = new QHash<QString, QHash<QString, QVariant> *>;
}

SettingsHivePrivate::~SettingsHivePrivate()
{
    foreach(const QString &key, store->keys())
        delete store->value(key);
    delete store;
}
