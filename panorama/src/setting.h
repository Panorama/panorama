#ifndef SETTING_H
#define SETTING_H

#include <QObject>
#include <QString>
#include <QHash>
#include <qdeclarative.h>

#include "settingssource.h"

/**
 * A QML object for accessing the settings API
 */
class Setting : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString  section READ section WRITE setSection NOTIFY sectionChanged)
    Q_PROPERTY(QString  key READ key WRITE setKey NOTIFY keyChanged)
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QVariant defaultValue READ defaultValue WRITE setDefaultValue NOTIFY defaultValueChanged)
public:
    /** Constructs a new Setting instance */
    explicit Setting(QObject *parent = 0);

    Setting(const QString &section, const QString &key, QObject *parent = 0);
    Setting(const QString &section, const QString &key, const QVariant &defaultValue, QObject *parent = 0);

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
    void setDefaultValue(const QVariant &value);

    /** Retrieves the default value of this setting */
    QVariant defaultValue() const
    {
        return _default;
    }

    /** Sets the value of this setting */
    void setValue(const QVariant &value);

    /** Retrieves the value of this setting */
    QVariant value() const;

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
    static void setSettingsSource(SettingsSource *value);

signals:
    /** This setting has a new section */
    void sectionChanged(const QString &section);

    /** The key for this setting was changed */
    void keyChanged(const QString &key);

    /** The default value for this section was changed */
    void defaultValueChanged(const QVariant &value);

    /** The value of this setting was changed */
    void valueChanged(const QVariant &value);

private slots:
    void handleFieldChange(const QString &section, const QString &key,
                           const QVariant &value);

private:
    void maybeInsertDefault();

    QString _section;
    QString _key;
    QVariant _default;

    static QString _defaultSection;
    static SettingsSource *_settings;
};

QML_DECLARE_TYPE(Setting);

#endif // SETTING_H
