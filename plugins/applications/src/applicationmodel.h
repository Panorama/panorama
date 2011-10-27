#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include "panoramainternal.h"

#include <QObject>
#include <QString>
#include <QAbstractItemModel>
#include <qdeclarative.h>
#include "application.h"

class ApplicationModelPrivate;

/**
 * A model for modelling a source of launchable applications.
 */
class ApplicationModel : public QAbstractListModel
{
    Q_OBJECT
    PANORAMA_DECLARE_PRIVATE(ApplicationModel)
public:
    /** Constructs a new ApplicationModel instance */
    explicit ApplicationModel(QObject *parent = 0);
    ~ApplicationModel();

    /** The roles that an ApplicationModel accepts */
    enum Roles
    {
        Id = Qt::UserRole,
        Name = Qt::UserRole + 1,
        Comment = Qt::UserRole + 2,
        Icon = Qt::UserRole + 3,
        Version = Qt::UserRole + 4,
        Categories = Qt::UserRole + 5,
        Preview = Qt::UserRole + 6,
        Clockspeed = Qt::UserRole + 7,
        PandoraId = Qt::UserRole + 8,
    };

    /** Returns the number of items in this model */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /** Returns the data at the specified index. */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /** Returns the header for each role */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    /** QML helper method that applies a filter to this model */
    Q_INVOKABLE QVariant inCategory(const QString &category);

    /** QML helper method that applies a filter to this model */
    Q_INVOKABLE QVariant matching(const QString &role, const QString &value);

    /** QML helper method that sorts this model */
    Q_INVOKABLE QVariant sortedBy(const QString &role, bool ascending);

    Q_INVOKABLE QVariant drop(int count);

    Q_INVOKABLE QVariant take(int count);

public slots:
    /** An Application should be added */
    void addApp(const Application &app, bool signalChange = true);

    /** An Application should be removed, if it exists */
    void removeApp(const Application &app, bool signalChange = true);

    /** The whole application set should be considered invalid and be reloaded */
    void invalidateData();
};

#endif // APPLICATIONMODEL_H
