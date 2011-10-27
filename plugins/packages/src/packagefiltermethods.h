#ifndef PACKAGEFILTERMETHODS_H
#define PACKAGEFILTERMETHODS_H

#include <QVariant>
#include <QString>

#include "packagefiltermodel.h"

/**
 * A helper class that provides methods for sorting and filtering
 * QAabstractItemModels.
 * This should only be used in conjunction with ApplicationModels since it's not
 * general-purpose.
 */
class PackageFilterMethods
{
public:
    /**
     * Applies a filter to source that filters out all packages except those
     * that have a category matching the regex given in "category". The source
     * object's data is not modified. Instead, a proxy model is returned with
     * the expected behavior.
     */
    static QVariant inCategory(QAbstractItemModel *source,
                               const QString &category);

    /**
     * Applies a filter to source that filters out all packages except those
     * that have a role specified by "role" matching the regex given in "value".
     * The source object's data is not modified. Instead, a proxy model is
     * returned with the expected behavior.
     */
    static QVariant matching(QAbstractItemModel *source, const QString &role,
                             const QString &value);

    /**
     * Returns a model that contains the same data as "source", only sorted. The
     * role to sort by is specified in "role", and "ascending" indicates whether
     * the sort should be ascending or descending.
     */
    static QVariant sortedBy(QAbstractItemModel *source, const QString &role,
                             bool ascending);

    static QVariant drop(QAbstractItemModel *source, int count);

    static QVariant take(QAbstractItemModel *source, int count);

private:
    PackageFilterMethods() {}

    PackageFilterMethods(const PackageFilterMethods&);

    PackageFilterMethods& operator=(const PackageFilterMethods&);
};

#endif // PACKAGEFILTERMETHODS_H
