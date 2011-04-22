#ifndef SETTINGSHIVE_H
#define SETTINGSHIVE_H

#include "settingssource.h"

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QHash>
#include <QSettings>

class SettingsHive : public SettingsSource
{
Q_OBJECT
public:
    explicit SettingsHive(QObject *parent = 0);

    ~SettingsHive();

    void writeSettings(QSettings &out) const;
    void readSettings(const QSettings &in);

    QVariant setting(const QString &section, const QString &key) const;

public slots:
    void setSetting(const QString &section, const QString &key,
                    const QVariant &value, SettingsSource::ChangeSource source = SettingsSource::Unknown);

private:
    QHash<QString, QHash<QString, QVariant> *> *_store;
};

#endif // SETTINGSHIVE_H
