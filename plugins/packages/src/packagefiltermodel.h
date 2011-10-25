#ifndef PACKAGEFILTERMODEL_H
#define PACKAGEFILTERMODEL_H

#include "panoramainternal.h"

#include <QSortFilterProxyModel>
#include <qdeclarative.h>

class PackageFilterModelPrivate;

/**
 * A proxy model for filtering an ApplicationModel
 */
class PackageFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT
    PANORAMA_DECLARE_PRIVATE(PackageFilterModel)
public:
    /** Constructs a new ApplicationFilterModel instance */
    explicit PackageFilterModel(QObject *parent = 0);
    ~PackageFilterModel();

    /**
     * Constructs a new PackageFilterModel instance with the given source
     * model
     */
    explicit PackageFilterModel(QAbstractItemModel *sourceModel,
                                    QObject *parent = 0);

    /**
     * Checks if the row with the given index should be filtered. The "parent"
     * parameter is ignored.
     */
    bool filterAcceptsRow(int source_row,
                          const QModelIndex &source_parent) const;

    void setDrop(int value);

    void setTake(int value);

    /** QML helper method that applies a filter to this model */
    Q_INVOKABLE QVariant inCategory(const QString &category);

    /** QML helper method that applies a filter to this model */
    Q_INVOKABLE QVariant matching(const QString &role, const QString &value);

    /** QML helper method that sorts this model */
    Q_INVOKABLE QVariant sortedBy(const QString &role, bool ascending);

    Q_INVOKABLE int numResults();

    Q_INVOKABLE QVariant drop(int count);

    Q_INVOKABLE QVariant take(int count);
};

#endif // CATEGORYFILTERMODEL_H
