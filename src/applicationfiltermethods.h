#ifndef APPLICATIONFILTERMETHODS_H
#define APPLICATIONFILTERMETHODS_H

#include <QVariant>
#include <QString>

#include "applicationfiltermodel.h"

/**
 * A helper class that provides methods for sorting and filtering
 * QAabstractItemModels.
 * This should only be used in conjunction with ApplicationModels since it's not
 * general-purpose.
 */
class ApplicationFilterMethods
{
public:
    /**
     * Applies a filter to source that filters out all applcations except those
     * that have a category matching the regex given in "category". The source
     * object's data is not modified. Instead, a proxy model is returned with
     * the expected behavior.
     */
    static QVariant inCategory(QAbstractItemModel *source,
                               const QString &category);

    /**
     * Applies a filter to source that filters out all applcations except those
     * that have a role specified by "role" matching the regex given in "value".
     * The source object's data is not modified. Instead, a proxy model is
     * returned with the expected behavior.
     */
    static QVariant matching(QAbstractItemModel *source, const QString &role,
                             const QString &value);

    /**
     * Returns a model that contains the same data as "source", only sorted. The
     * role to sort by is specified in "role", and "ascending" indicates whether
     * the sort shoul dbe ascending or descending.
     */
    static QVariant sortedBy(QAbstractItemModel *source, const QString &role,
                             bool ascending);

private:
    ApplicationFilterMethods() {};

    ApplicationFilterMethods(const ApplicationFilterMethods&);

    ApplicationFilterMethods& operator=(const ApplicationFilterMethods&);
};

#endif // APPLICATIONFILTERMETHODS_H
