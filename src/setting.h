#ifndef SETTING_H
#define SETTING_H

#include <QObject>
#include <QString>
#include <QHash>

class Setting : public QObject
{
Q_OBJECT
Q_PROPERTY(QString section READ section WRITE setSection NOTIFY sectionChanged)
Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit Setting(QObject *parent = 0);

    void setSection(const QString &section);
    QString section() const;

    void setKey(const QString &key);
    QString key() const;

    void setValue(const QString &value);
    QString value() const;

    static void setDefaultSection(const QString &section);
    static void setSettingsSource(QHash<QString, QHash<QString, QString> *> *value);

signals:
    void sectionChanged(const QString &section);
    void keyChanged(const QString &key);
    void valueChanged(const QString &value);

private:
    QString _section;
    QString _key;
    static QString _defaultSection;
    static QHash<QString, QHash<QString, QString> *> *_settings;
};

#endif // SETTING_H
