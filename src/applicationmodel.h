#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <qml.h>
#include "appaccumulator.h"
#include "application.h"
#include "applicationfiltermethods.h"

class ApplicationModel : public QAbstractListModel
{
Q_OBJECT
public:
    /** Constructs a new ApplicationModel instance */
    explicit ApplicationModel(QObject *parent = 0);

    enum Roles
    {
        Id = Qt::UserRole,
        Name = Qt::UserRole + 1,
        Comment = Qt::UserRole + 2,
        Icon = Qt::UserRole + 3,
        Version = Qt::UserRole + 4,
        Categories = Qt::UserRole + 5,
        Preview = Qt::UserRole + 6,
        Clockspeed = Qt::UserRole + 7
    };

    /** Returns the number of items in this model */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /** Returns the data at the specified index. */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /** Returns the header for each role */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    Q_INVOKABLE QVariant inCategory(const QString &category); //TODO: Remove code duplication!!
    Q_INVOKABLE QVariant matching(const QString &role, const QString &value);
    Q_INVOKABLE QVariant sortedBy(const QString &role, bool ascending);

public slots:
    /** An Application should be added */
    void addApp(const Application &app);
    /** An Application should be removed, if it exists */
    void removeApp(const Application &app);

private:
    QList<Application> _apps;
    QHash<int, QByteArray> _roles;
};

#endif // APPLICATIONMODEL_H
