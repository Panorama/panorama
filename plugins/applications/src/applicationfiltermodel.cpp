#include "applicationfiltermodel.h"

#include "applicationfiltermethods.h"
#include "applicationmodel.h"

class ApplicationFilterModelPrivate
{
    PANORAMA_DECLARE_PUBLIC(ApplicationFilterModel);
public:
    explicit ApplicationFilterModelPrivate();
    int take;
    int drop;
};

ApplicationFilterModel::ApplicationFilterModel(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    PANORAMA_INITIALIZE(ApplicationFilterModel);
}

ApplicationFilterModel::~ApplicationFilterModel()
{
    PANORAMA_UNINITIALIZE(ApplicationFilterModel);
}

ApplicationFilterModel::ApplicationFilterModel(QAbstractItemModel *sourceModel,
                                               QObject *parent) :
    QSortFilterProxyModel(parent)
{
    PANORAMA_INITIALIZE(ApplicationFilterModel);
    setSourceModel(sourceModel);
    setRoleNames(sourceModel->roleNames());
}

bool ApplicationFilterModel::filterAcceptsRow(int sourceRow,
                                              const QModelIndex &sourceParent)
    const
{
    PANORAMA_PRIVATE(const ApplicationFilterModel);
    if(sourceRow < priv->drop || (priv->take && (sourceRow >= priv->drop + priv->take)))
        return false;

    if(filterRole() == ApplicationModel::Categories)
    {
        const QModelIndex idx = sourceModel()->index(sourceRow, 0,
                                                     sourceParent);
        QStringList categories =
                sourceModel()->data(idx, ApplicationModel::Categories)
                    .toStringList();

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
    return ApplicationFilterMethods::inCategory(this, category);
}

QVariant ApplicationFilterModel::matching(const QString &role,
                                          const QString &value)
{
    return ApplicationFilterMethods::matching(this, role, value);
}

QVariant ApplicationFilterModel::containing(const QString &role,
                                            const QString &value)
{
    return ApplicationFilterMethods::containing(this, role, value);
}

QVariant ApplicationFilterModel::sortedBy(const QString &role, bool ascending)
{
    return ApplicationFilterMethods::sortedBy(this, role, ascending);
}

QVariant ApplicationFilterModel::drop(int count)
{
    return ApplicationFilterMethods::drop(this, count);
}

QVariant ApplicationFilterModel::take(int count)
{
    return ApplicationFilterMethods::take(this, count);
}

void ApplicationFilterModel::setDrop(int value)
{
    PANORAMA_PRIVATE(ApplicationFilterModel);
    priv->drop = value;
}

void ApplicationFilterModel::setTake(int value)
{
    PANORAMA_PRIVATE(ApplicationFilterModel);
    priv->take = value;
}

ApplicationFilterModelPrivate::ApplicationFilterModelPrivate()
    : take(0), drop(0)
{}
