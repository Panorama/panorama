#include "applications.h"

Applications::Applications(QObject *parent) :
    QObject(parent)
{
}

ApplicationsAttached *Applications::qmlAttachedProperties(QObject *parent)
{
    return new ApplicationsAttached(parent);
}
