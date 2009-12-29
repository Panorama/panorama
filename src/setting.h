#ifndef SETTING_H
#define SETTING_H

#include <QObject>
#include <QString>
#include <QHash>
#include <qml.h>

/**
 * A small helper class for the Setting class
 */ //TODO: move to private header
class PrivatePropagator : public QObject {
    Q_OBJECT
public:
    explicit PrivatePropagator(QObject *parent = 0);

public slots:
    void changeField(const QString &section, const QString &key, const QString &value);

signals:
    void fieldChanged(const QString &section, const QString &key, const QString &value);
};

/**
 * A QML object for accessing the settings API
 */
class Setting : public QObject
{
Q_OBJECT
Q_PROPERTY(QString section READ section WRITE setSection NOTIFY sectionChanged)
Q_PROPERTY(QString key READ key WRITE setKey NOTIFY keyChanged)
Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
Q_PROPERTY(QString defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)
public:
    /** Constructs a new Setting instance */
    explicit Setting(QObject *parent = 0);

    /** Sets the section of this setting */
    void setSection(const QString &section);

    /** Retrieves the section of this setting */
    QString section() const
    {
        return _section;
    }

    /** Sets the key for this setting */
    void setKey(const QString &key);

    /** Retrieves the key for this setting */
    QString key() const
    {
        return _key;
    }

    /** Sets the default value of this setting */
    void setDefaultValue(const QString &value);

    /** Retrieves the default value of this setting */
    QString defaultValue() const
    {
        return _default;
    }

    /** Sets the value of this setting */
    void setValue(const QString &value);

    /** Retrieves the value of this setting */
    QString value() const;

    /** Sets the default section for all Setting instances */
    static void setDefaultSection(const QString &section)
    {
        _defaultSection = section;
    }

    /** Retrieves the default section for all Setting instances */
    static QString defaultSection() {
        return _defaultSection;
    }

    /** Sets the settings source for the settings API */
    static void setSettingsSource(
            QHash<QString, QHash<QString, QString> *> *value);

signals:
    /** This setting has a new section */
    void sectionChanged(const QString &section);

    /** The key for this setting was changed */
    void keyChanged(const QString &key);

    /** The default value for this section was changed */
    void defaultValueChanged(const QString &value);

    /** The value of this setting was changed */
    void valueChanged(const QString &value);

private slots:
    void handleFieldChange(const QString &section, const QString &key,
                           const QString &value);

private:
    void maybeInsertDefault();

    QString _section;
    QString _key;
    QString _default;

    static PrivatePropagator _prop;
    static QString _defaultSection;
    static QHash<QString, QHash<QString, QString> *> *_settings;
};

QML_DECLARE_TYPE(Setting);

#endif // SETTING_H
