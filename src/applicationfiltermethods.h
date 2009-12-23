#ifndef APPLICATIONFILTERMETHODS_H
#define APPLICATIONFILTERMETHODS_H

#include <QVariant>
#include <QString>
#include "applicationfiltermodel.h"

class ApplicationFilterMethods
{
public:
    static QVariant inCategory(QAbstractItemModel *source, const QString &category);
    static QVariant matching(QAbstractItemModel *source, const QString &role, const QString &value);
    static QVariant sortedBy(QAbstractItemModel *source, const QString &role, bool ascending);
private:
    ApplicationFilterMethods() {};
    ApplicationFilterMethods(const ApplicationFilterMethods&);
    ApplicationFilterMethods& operator=(const ApplicationFilterMethods&);
};

#endif // APPLICATIONFILTERMETHODS_H
