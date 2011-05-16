#include "systeminformation.h"

SystemInformation::SystemInformation(QObject *parent)
    : QObject(parent)
{}

SystemInformationAttached *SystemInformation::qmlAttachedProperties(QObject *parent)
{
    return new SystemInformationAttached(parent);
}
