#ifndef SYSTEMINFORMATION_H
#define SYSTEMINFORMATION_H

#include <qdeclarative.h>

#include "systeminformationattached.h"

class SystemInformation : public QObject
{
public:
    explicit SystemInformation(QObject *parent = 0);

    static SystemInformationAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(SystemInformation, QML_HAS_ATTACHED_PROPERTIES)

#endif // SYSTEMINFORMATION_H
