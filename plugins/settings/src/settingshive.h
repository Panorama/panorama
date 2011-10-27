#ifndef SETTINGSHIVE_H
#define SETTINGSHIVE_H

#include "panoramainternal.h"

#include <QObject>
#include <QString>
#include <QSettings>

#include "settingssource.h"

class SettingsHivePrivate;

class SettingsHive : public SettingsSource
{
    Q_OBJECT
    PANORAMA_DECLARE_PRIVATE(SettingsHive)
public:
    explicit SettingsHive(QObject *parent = 0);
    SettingsHive(const QSettings &in, QObject *parent = 0);
    ~SettingsHive();

    void writeSettings(QSettings &out) const;
    void readSettings(const QSettings &in);

    QVariant setting(const QString &section, const QString &key) const;

public slots:
    void setSetting(const QString &section, const QString &key,
                    const QVariant &value, SettingsSource::ChangeSource source = SettingsSource::Unknown);
};

#endif // SETTINGSHIVE_H
