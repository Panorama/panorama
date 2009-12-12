#include "applicationfiltermodel.h"

ApplicationFilterModel::ApplicationFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{}

ApplicationFilterModel::ApplicationFilterModel(QAbstractItemModel *sourceModel, QObject *parent) :
    QSortFilterProxyModel(parent)
{
    setSourceModel(sourceModel);
    setRoleNames(sourceModel->roleNames());
}

bool ApplicationFilterModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if(filterRole() == ApplicationModel::Categories)
    {
        const QModelIndex idx = sourceModel()->index(sourceRow, 0, sourceParent);
        QStringList categories = sourceModel()->data(idx, ApplicationModel::Categories).toStringList();

        if(categories.isEmpty())
            categories.append("NoCategory");

        foreach(const QString &category, categories)
            if(filterRegExp().exactMatch(category))
                return true;

        return false;
    }
    else
        return QSortFilterProxyModel::filterAcceptsRow(sourceRow, sourceParent);
}

QVariant ApplicationFilterModel::inCategory(const QString &category)
{
    ApplicationFilterModel *result = new ApplicationFilterModel(this, this);
    result->setFilterRole(ApplicationModel::Categories);
    result->setFilterRegExp(category);
    return QVariant::fromValue((QObject *)result);
}

QVariant ApplicationFilterModel::matching(const QString &role, const QString &value)
{
    ApplicationFilterModel *result = new ApplicationFilterModel(this, this);
    result->setFilterRole(roleNames().key(role.toLocal8Bit(), ApplicationModel::Name));
    result->setFilterWildcard(value);
    result->setFilterCaseSensitivity(Qt::CaseInsensitive);
    return QVariant::fromValue((QObject *)result);
}

QVariant ApplicationFilterModel::sortedBy(const QString &role, bool ascending)
{
    ApplicationFilterModel *result = new ApplicationFilterModel(this, this);
    result->setSortRole(roleNames().key(role.toLocal8Bit(), ApplicationModel::Name));
    result->setSortCaseSensitivity(Qt::CaseInsensitive);
    result->sort(0, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
    return QVariant::fromValue((QObject *)result);
}
