#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "panoramainternal.h"

#include <QObject>
#include <QString>
#include <QVariant>

#include "settingshive.h"

class ConfigurationPrivate;

/**
 * Represents a configuration file for the Panorama application
 */
class Configuration : public QObject
{
    Q_OBJECT
    PANORAMA_DECLARE_PRIVATE(Configuration)
public:
    /** Constructs a new Configuration instance */
    explicit Configuration(QObject *parent = 0);
    ~Configuration();

    /** Gets a pointer to the raw setting registry. */
    SettingsHive *generalConfig() const;

public slots:
    void loadConfiguration();
    void saveConfiguration();

private slots:
    void reactToChange(const QString&, const QString&, const QVariant&,
                       SettingsSource::ChangeSource source);
};

#endif // CONFIGURATION_H
