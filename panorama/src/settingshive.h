#ifndef SETTINGSHIVE_H
#define SETTINGSHIVE_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QHash>
#include <QSettings>

class SettingsHive : public QObject
{
Q_OBJECT
public:
    explicit SettingsHive(QObject *parent = 0);

    ~SettingsHive();

    enum ChangeSource {
        Unknown,
        Internal,
        File,
        External
    };

    void writeSettings(QSettings &out) const;

    QVariant setting(const QString &section, const QString &key) const;

signals:
    void settingChanged(const QString &section, const QString &key,
                        const QVariant &value, ChangeSource source);

public slots:
    void setSetting(const QString &section, const QString &key,
                    const QVariant &value, ChangeSource source = Unknown);

private:
    QHash<QString, QHash<QString, QVariant> *> *_store;
};

#endif // SETTINGSHIVE_H
