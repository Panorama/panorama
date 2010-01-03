#ifndef PANORAMASKIN_H
#define PANORAMASKIN_H

#include <QObject>
#include <QString>
#include <QProcess>
#include <QAbstractItemModel>
#include <QtDeclarative/QmlGraphicsItem>

#include "appaccumulator.h"
#include "constants.h"
#include "setting.h"

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
Q_PROPERTY(QString settingsSection READ settingsSection WRITE setSettingsSection)
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

    /** Gets the default settings section */
    QString settingsSection() const;

    /** Sets the default settings section */
    void setSettingsSection(const QString &);

    /** Gets the current application model */
    QVariant applications() const;

    /** Sets the application model source */
    static void setApplicationsSource(QAbstractItemModel *value);

    /** QML helper method for executing the application with the given id */
    Q_INVOKABLE void execute(const QString &sha1);

public slots:
    /** Called when application data has changed */
    void propagateApplicationDataChange();

    /** Called when this instance has been loaded */
    void indicateLoadFinished();

signals:
    /** The application source has been updated */
    void applicationsUpdated(QVariant value);

    /** This UI has finished loading */
    void loaded();

private:
    QString _name;
    QString _description;
    QString _author;

    static QVariant _apps;
};

//Makes this type available in QML
QML_DECLARE_TYPE(PanoramaUI);

#endif // PANORAMASKIN_H
