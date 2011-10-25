#include "applicationfiltermethods.h"

#include "applicationmodel.h"

QVariant ApplicationFilterMethods::inCategory(QAbstractItemModel *source,
                                              const QString &category)
{
    ApplicationFilterModel *result = new ApplicationFilterModel(source, source);

    result->setParent(source);
    result->setFilterRole(ApplicationModel::Categories);
    result->setFilterRegExp(category);

    return QVariant::fromValue((QObject *)result);
}

QVariant ApplicationFilterMethods::matching(QAbstractItemModel *source,
                                            const QString &role,
                                            const QString &value)
{
    ApplicationFilterModel *result = new ApplicationFilterModel(source, source);

    result->setFilterRole(source->roleNames().key(role.toLocal8Bit(),
                                                  ApplicationModel::Name));
    result->setFilterRegExp(value);
    result->setFilterCaseSensitivity(Qt::CaseInsensitive);

    return QVariant::fromValue((QObject *)result);
}

QVariant ApplicationFilterMethods::sortedBy(QAbstractItemModel *source,
                                            const QString &role, bool ascending)
{
    ApplicationFilterModel *result = new ApplicationFilterModel(source, source);

    result->setSortRole(source->roleNames().key(role.toLocal8Bit(),
                                                ApplicationModel::Name));
    result->setSortCaseSensitivity(Qt::CaseInsensitive);
    result->sort(0, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);

    return QVariant::fromValue((QObject *)result);
}

QVariant ApplicationFilterMethods::drop(QAbstractItemModel *source, int count)
{
    ApplicationFilterModel *result = new ApplicationFilterModel(source, source);

    result->setDrop(count);

    return QVariant::fromValue((QObject *)result);
}

QVariant ApplicationFilterMethods::take(QAbstractItemModel *source, int count)
{
    ApplicationFilterModel *result = new ApplicationFilterModel(source, source);

    result->setTake(count);

    return QVariant::fromValue((QObject *)result);
}
