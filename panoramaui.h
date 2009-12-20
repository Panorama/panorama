#ifndef PANORAMASKIN_H
#define PANORAMASKIN_H

#include <QObject>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QProcess>
#include <QAbstractItemModel>
#include <QtDeclarative/QmlGraphicsItem>

#include "appaccumulator.h"
#include "constants.h"

/**
 * The base class for all PanoramaUI instances.
 * This class is extended from actual .qml files via the QtScript core
 */
class PanoramaUI : public QmlGraphicsItem
{
Q_OBJECT
Q_PROPERTY(QString  name        READ name           WRITE setName)
Q_PROPERTY(QString  description READ description    WRITE setDescription)
Q_PROPERTY(QString  author      READ author         WRITE setAuthor)
Q_PROPERTY(QString  settingsKey READ settingsKey    WRITE setSettingsKey)
Q_PROPERTY(QVariant applications READ applications  NOTIFY applicationsUpdated)

public:
    /** Constructs a new PanoramaUI instance */
    explicit PanoramaUI(QmlGraphicsItem *parent = 0);

    /** Gets the name */
    QString name() const;
    /** Sets the name */
    void setName(const QString&);

    /** Gets the description */
    QString description() const;
    /** Sets the description */
    void setDescription(const QString&);

    /** Gets the author */
    QString author() const;
    /** Sets the author */
    void setAuthor(const QString&);

    QString settingsKey() const;
    void setSettingsKey(const QString &);

    QVariant applications() const;

    static void setApplicationsSource(QAbstractItemModel *value);

    static void setSettingsSource(QHash<QString, QHash<QString, QString> *> *value);

    Q_INVOKABLE void setSetting(const QString &key, const QString &value);
    Q_INVOKABLE QString setting(const QString &key);

    Q_INVOKABLE void setSharedSetting(const QString &section, const QString &key, const QString &value);
    Q_INVOKABLE QString sharedSetting(const QString &section, const QString &key);

    Q_INVOKABLE void execute(const QString &sha1);

public slots:
    void applicationDataChanged();
    void loaded();

signals:
    void applicationsUpdated(QVariant value);
    void load();

private:
    QString _name;
    QString _description;
    QString _author;
    QString _settingsKey;
    static QHash<QString, QHash<QString, QString> *> *_settings;
    static QVariant _apps;
};

//Makes this type available in QML
QML_DECLARE_TYPE(PanoramaUI);

#endif // PANORAMASKIN_H
