#include "packagefiltermodel.h"

#include "packagefiltermethods.h"
#include "milkymodel.h"

class PackageFilterModelPrivate
{
    PANORAMA_DECLARE_PUBLIC(PackageFilterModel);
public:
    explicit PackageFilterModelPrivate();
    int take;
    int drop;
};

PackageFilterModel::PackageFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    PANORAMA_INITIALIZE(PackageFilterModel);
}

PackageFilterModel::~PackageFilterModel()
{
    PANORAMA_UNINITIALIZE(PackageFilterModel);
}

PackageFilterModel::PackageFilterModel(QAbstractItemModel *sourceModel,
                                               QObject *parent) :
    QSortFilterProxyModel(parent)
{
    PANORAMA_INITIALIZE(PackageFilterModel);
    setSourceModel(sourceModel);
    setRoleNames(sourceModel->roleNames());
    setDynamicSortFilter(true);
}

bool PackageFilterModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent)
    const
{
    PANORAMA_PRIVATE(const PackageFilterModel);
    if(sourceRow < priv->drop || (priv->take && (sourceRow >= priv->drop + priv->take)))
        return false;

    if(filterRole() == MilkyModel::Group)
    {
        const QModelIndex idx = sourceModel()->index(sourceRow, 0,
                                                     sourceParent);
        QStringList categories =
                sourceModel()->data(idx, MilkyModel::Group)
                    .toStringList();

        foreach(const QString &category, categories)
            if(filterRegExp().exactMatch(category))
                return true;

        return false;
    }
    else
        return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
}

QVariant PackageFilterModel::inCategory(const QString &category)
{
    return PackageFilterMethods::inCategory(this, category);
}

QVariant PackageFilterModel::matching(const QString &role,
                                          const QString &value)
{
    return PackageFilterMethods::matching(this, role, value);
}

QVariant PackageFilterModel::sortedBy(const QString &role, bool ascending)
{
    return PackageFilterMethods::sortedBy(this, role, ascending);
}

int PackageFilterModel::numResults()
{
    return rowCount();
}

QVariant PackageFilterModel::drop(int count)
{
    return PackageFilterMethods::drop(this, count);
}

QVariant PackageFilterModel::take(int count)
{
    return PackageFilterMethods::take(this, count);
}

void PackageFilterModel::setDrop(int value)
{
    PANORAMA_PRIVATE(PackageFilterModel);
    priv->drop = value;
}

void PackageFilterModel::setTake(int value)
{
    PANORAMA_PRIVATE(PackageFilterModel);
    priv->take = value;
}

PackageFilterModelPrivate::PackageFilterModelPrivate()
    : take(0), drop(0)
{}
