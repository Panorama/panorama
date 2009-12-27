#ifndef SETTING_H
#define SETTING_H

#include <QObject>
#include <QString>
#include <QHash>
#include <qml.h>


class PrivatePropagator : public QObject {
    Q_OBJECT
public:
    explicit PrivatePropagator(QObject *parent = 0);
public slots:
    void changeField(const QString &section, const QString &key, const QString &value);
signals:
    void fieldChanged(const QString &section, const QString &key, const QString &value);
};

class Setting : public QObject
{
Q_OBJECT
Q_PROPERTY(QString section READ section WRITE setSection NOTIFY sectionChanged)
Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
public:
    explicit Setting(QObject *parent = 0);

    void setSection(const QString &section);
    QString section() const { return _section; }

    void setKey(const QString &key);
    QString key() const { return _key; }

    void setValue(const QString &value);
    QString value() const;

    static void setDefaultSection(const QString &section) { _defaultSection = section; }
    static QString defaultSection() { return _defaultSection; }

    static void setSettingsSource(QHash<QString, QHash<QString, QString> *> *value);

signals:
    void sectionChanged(const QString &section);
    void keyChanged(const QString &key);
    void valueChanged(const QString &value);

private slots:
    void handleFieldChange(const QString &section, const QString &key, const QString &value);

private:
    QString _section;
    QString _key;
    static PrivatePropagator _prop;
    static QString _defaultSection;
    static QHash<QString, QHash<QString, QString> *> *_settings;
};
QML_DECLARE_TYPE(Setting)

#endif // SETTING_H
