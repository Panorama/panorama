#include "packagefiltermethods.h"

#include "milkymodel.h"

QVariant PackageFilterMethods::inCategory(QAbstractItemModel *source,
                                              const QString &category)
{
    PackageFilterModel *result = new PackageFilterModel(source, source);

    result->setParent(source);
    result->setFilterRole(MilkyModel::CategoriesString);
    QString filter = QString("%1%2%3").arg("(^|;)").arg(category).arg("($|;)");
    result->setFilterRegExp(filter);

    return QVariant::fromValue((QObject *)result);
}

QVariant PackageFilterMethods::matching(QAbstractItemModel *source,
                                            const QString &role,
                                            const QString &value)
{
    PackageFilterModel *result = new PackageFilterModel(source, source);

    result->setFilterRole(source->roleNames().key(role.toLocal8Bit(),
                                                  MilkyModel::Title));
    result->setFilterRegExp(value);
    result->setFilterCaseSensitivity(Qt::CaseInsensitive);

    return QVariant::fromValue((QObject *)result);
}

QVariant PackageFilterMethods::sortedBy(QAbstractItemModel *source,
                                            const QString &role, bool ascending)
{
    PackageFilterModel *result = new PackageFilterModel(source, source);

    result->setSortRole(source->roleNames().key(role.toLocal8Bit(),
                                                MilkyModel::Title));
    result->setSortCaseSensitivity(Qt::CaseInsensitive);
    result->sort(0, ascending ? Qt::AscendingOrder : Qt::DescendingOrder);

    return QVariant::fromValue((QObject *)result);
}

QVariant PackageFilterMethods::drop(QAbstractItemModel *source, int count)
{
    PackageFilterModel *result = new PackageFilterModel(source, source);

    result->setDrop(count);

    return QVariant::fromValue((QObject *)result);
}

QVariant PackageFilterMethods::take(QAbstractItemModel *source, int count)
{
    PackageFilterModel *result = new PackageFilterModel(source, source);

    result->setTake(count);

    return QVariant::fromValue((QObject *)result);
}
