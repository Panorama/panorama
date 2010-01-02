#ifndef SETTINGSHIVE_H
#define SETTINGSHIVE_H

#include <QObject>
#include <QString>
#include <QTextStream>
#include <QHash>

class SettingsHive : public QObject
{
Q_OBJECT
public:
    explicit SettingsHive(QObject *parent = 0);

    ~SettingsHive();

    void writeIni(QTextStream &out) const;

    QString setting(const QString &section, const QString &key) const;

signals:
    void settingChanged(const QString &section, const QString &key,
                        const QString &value);

public slots:
    void setSetting(const QString &section, const QString &key,
                    const QString &value);

private:
    QHash<QString, QHash<QString, QString> *> *_store;
};

#endif // SETTINGSHIVE_H
