#ifndef SETTING_H
#define SETTING_H

#include "panoramainternal.h"

#include <QObject>
#include <QString>
#include <QVariant>
#include <qdeclarative.h>

#include "settingssource.h"

class SettingPrivate;

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
    PANORAMA_DECLARE_PRIVATE(Setting)
public:
    /** Constructs a new Setting instance */
    explicit Setting(QObject *parent = 0);
    ~Setting();

    Setting(const QString &section, const QString &key, QObject *parent = 0);
    Setting(const QString &section, const QString &key, const QVariant &defaultValue, QObject *parent = 0);

    /** Sets the section of this setting */
    void setSection(const QString &section);

    /** Retrieves the section of this setting */
    QString section() const;

    /** Sets the key for this setting */
    void setKey(const QString &key);

    /** Retrieves the key for this setting */
    QString key() const;

    /** Sets the default value of this setting */
    void setDefaultValue(const QVariant &value);

    /** Retrieves the default value of this setting */
    QVariant defaultValue() const;

    /** Sets the value of this setting */
    void setValue(const QVariant &value);

    /** Retrieves the value of this setting */
    QVariant value() const;

signals:
    /** This setting has a new section */
    void sectionChanged(const QString &section);

    /** The key for this setting was changed */
    void keyChanged(const QString &key);

    /** The default value for this section was changed */
    void defaultValueChanged(const QVariant &value);

    /** The value of this setting was changed */
    void valueChanged(const QVariant &value);

protected slots:
    void handleFieldChange(const QString &section, const QString &key,
                           const QVariant &value);
};

QML_DECLARE_TYPE(Setting);

#endif // SETTING_H
