#ifndef CATEGORYFILTERMODEL_H
#define CATEGORYFILTERMODEL_H

#include <QSortFilterProxyModel>
#include <qml.h>
#include "applicationmodel.h"

class ApplicationModel;

class ApplicationFilterModel : public QSortFilterProxyModel
{
Q_OBJECT
public:
    explicit ApplicationFilterModel(QObject *parent = 0);
    explicit ApplicationFilterModel(QAbstractItemModel *sourceModel, QObject *parent = 0);

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

    Q_INVOKABLE QVariant inCategory(const QString &category);
    Q_INVOKABLE QVariant matching(const QString &role, const QString &value);
    Q_INVOKABLE QVariant sortedBy(const QString &role, bool ascending);
};

#endif // CATEGORYFILTERMODEL_H
