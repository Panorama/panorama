#ifndef PANORAMASKIN_H
#define PANORAMASKIN_H

#include <QObject>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QProcess>
#include <QAbstractItemModel>
#include <QFontDatabase>
#include <QtDeclarative/QmlContext>
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
Q_PROPERTY(QString  settingsSection READ settingsSection    WRITE setSettingsSection)
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

    QString settingsSection() const;
    void setSettingsSection(const QString &);

    QVariant applications() const;

    static void setApplicationsSource(QAbstractItemModel *value);

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
    static QVariant _apps;
};

//Makes this type available in QML
QML_DECLARE_TYPE(PanoramaUI);

#endif // PANORAMASKIN_H
