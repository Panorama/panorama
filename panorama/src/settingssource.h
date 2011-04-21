#ifndef SETTINGSSOURCE_H
#define SETTINGSSOURCE_H

#include <QObject>

class SettingsSource : public QObject
{
    Q_OBJECT
public:
    explicit SettingsSource(QObject *parent = 0);

    enum ChangeSource {
        Unknown,
        Internal,
        File,
        External
    };

    virtual QVariant setting(const QString &section, const QString &key) const = 0;

signals:
    void settingChanged(const QString &section, const QString &key,
                        const QVariant &value, SettingsSource::ChangeSource source);

public slots:
    virtual void setSetting(const QString &section, const QString &key,
                            const QVariant &value, SettingsSource::ChangeSource source = SettingsSource::Unknown) = 0;
};

#endif // SETTINGSSOURCE_H
