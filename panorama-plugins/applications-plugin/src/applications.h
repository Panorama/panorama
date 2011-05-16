#ifndef APPLICATIONS_H
#define APPLICATIONS_H

#include <QObject>
#include "applicationattached.h"
#include "qdeclarative.h"

class Applications : public QObject
{
    Q_OBJECT
public:
    explicit Applications(QObject *parent = 0);

    static ApplicationsAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(Applications, QML_HAS_ATTACHED_PROPERTIES)

#endif // APPLICATIONS_H
