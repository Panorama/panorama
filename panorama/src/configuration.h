#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QFileSystemWatcher>

#include "settingshive.h"

/**
 * Represents a configuration file for the Panorama application
 */
class Configuration : public QObject
{
Q_OBJECT
public:
    /** Constructs a new Configuration instance */
    explicit Configuration(QObject *parent = 0);

    /** Gets a pointer to the raw setting registry. */
    SettingsHive *generalConfig() const;

public slots:
    void loadConfiguration();
    void saveConfiguration();

private slots:
    void reactToChange(const QString&, const QString&, const QVariant&,
                       SettingsSource::ChangeSource source);

private:
    void initConfiguration();
    QSettings *_settings;
    SettingsHive *_hive;
    QFileSystemWatcher _watcher;
};

#endif // CONFIGURATION_H
