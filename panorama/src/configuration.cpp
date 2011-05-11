#include "configuration.h"

#include <QFileSystemWatcher>
#include <QFileInfo>
#include <QStringList>
#include <QDebug>
#include "constants.h"

class ConfigurationPrivate
{
    PANORAMA_DECLARE_PUBLIC(Configuration)
public:
    void initConfiguration();
    QSettings *settings;
    SettingsHive *hive;
    QFileSystemWatcher watcher;
};

Configuration::Configuration(QObject *parent) :
        QObject(parent)
{
    PANORAMA_INITIALIZE(Configuration);
    priv->hive = new SettingsHive(this);
    priv->settings = 0;

    connect(&priv->watcher, SIGNAL(fileChanged(QString)),
            this, SLOT(loadConfiguration()));
    connect(priv->hive, SIGNAL(settingChanged(QString,QString,QVariant,SettingsSource::ChangeSource)),
            this, SLOT(reactToChange(QString,QString,QVariant,SettingsSource::ChangeSource)));
}

Configuration::~Configuration()
{
    PANORAMA_UNINITIALIZE(Configuration);
}

void Configuration::loadConfiguration()
{
    PANORAMA_PRIVATE(Configuration);
    priv->initConfiguration();
    priv->settings->sync();
    priv->hive->readSettings(*priv->settings);

    const QString fileName = priv->settings->fileName();
    if(QFileInfo(fileName).exists() && !priv->watcher.files().contains(fileName))
        priv->watcher.addPath(fileName);
}

void Configuration::saveConfiguration()
{
    PANORAMA_PRIVATE(Configuration);
    priv->initConfiguration();
    priv->hive->writeSettings(*priv->settings);
    priv->settings->sync();
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
    PANORAMA_PRIVATE(const Configuration);
    return priv->hive;
}

void ConfigurationPrivate::initConfiguration()
{
    PANORAMA_PUBLIC(Configuration);
    if(!settings) {
#ifdef PANDORA
        settings = new QSettings(CONFIG_FILE, QSettings::IniFormat, pub);
#else
        settings = new QSettings(QSettings::UserScope, "panorama", "core", pub);
#endif
        if(settings->allKeys().isEmpty()) {
            qWarning() << "Warning: No configuration file detected, creating default configuration.";
            settings->setValue("panorama/uiDirectory", "interfaces");
            settings->setValue("panorama/ui", "Test");
            settings->setValue("panorama/fullscreen", false);
            settings->setValue("system/clockspeed", 600);
            settings->setValue("system/favorites", "");
            settings->sync();
        }
        watcher.addPath(settings->fileName());
        qDebug() << "Settings are saved in" << settings->fileName();
    }
}
