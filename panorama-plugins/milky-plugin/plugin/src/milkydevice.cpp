#include "milkydevice.h"

MilkyDevice::MilkyDevice(QObject *parent) :
    QObject(parent), device(), mountPoint(), size(0), free(0), freeForSuperuser(0)
{
}

MilkyDevice::MilkyDevice(_m_dev_struct* const device, QObject *parent) :
    QObject(parent), device(device->dev), mountPoint(device->mount),
    size(device->size), free(device->free), freeForSuperuser(device->available)
{
}

MilkyDevice::MilkyDevice(MilkyDevice const& other, QObject *parent) :
    QObject(parent), device(other.device), mountPoint(other.mountPoint), size(other.size), free(other.free), freeForSuperuser(other.freeForSuperuser)
{
}


MilkyDevice const& MilkyDevice::operator=(MilkyDevice const& other)
{
    if(this != &other)
    {
        device = other.device;
        mountPoint = other.mountPoint;
        size = other.size;
        free = other.free;
        freeForSuperuser = other.freeForSuperuser;
    }

    return *this;
}

QString MilkyDevice::getDevice() const
{
    return device;
}

QString MilkyDevice::getMountPoint() const
{
    return mountPoint;
}

int MilkyDevice::getSize() const
{
    return size;
}

int MilkyDevice::getFree() const
{
    return free;
}

int MilkyDevice::getFreeForSuperuser() const
{
    return freeForSuperuser;
}

void MilkyDevice::setDevice(QString newDevice)
{
    if(newDevice != device)
    {
        device = newDevice;
        emit deviceChanged(device);
    }
}

void MilkyDevice::setMountPoint(QString newMountPoint)
{
    if(newMountPoint != mountPoint)
    {
        mountPoint = newMountPoint;
        emit mountPointChanged(mountPoint);
    }
}

void MilkyDevice::setSize(int newSize)
{
    if(newSize != size)
    {
        size = newSize;
        emit sizeChanged(size);
    }
}

void MilkyDevice::setFree(int newFree)
{
    if(newFree != free)
    {
        free = newFree;
        emit freeChanged(free);
    }
}

void MilkyDevice::setFreeForSuperuser(int newFreeForSuperuser)
{
    if(newFreeForSuperuser != freeForSuperuser)
    {
        freeForSuperuser = newFreeForSuperuser;
        emit freeForSuperuserChanged(freeForSuperuser);
    }
}

