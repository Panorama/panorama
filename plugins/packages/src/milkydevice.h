#ifndef MILKYDEVICE_H
#define MILKYDEVICE_H

#include <QObject>
#include <QMetaType>
#include "milky/milky.h"

class MilkyDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString device READ getDevice WRITE setDevice NOTIFY deviceChanged);
    Q_PROPERTY(QString mountPoint READ getMountPoint WRITE setMountPoint NOTIFY mountPointChanged);
    Q_PROPERTY(int size READ getSize WRITE setSize NOTIFY sizeChanged);
    Q_PROPERTY(int free READ getFree WRITE setFree NOTIFY freeChanged);
    Q_PROPERTY(int freeForSuperuser READ getFreeForSuperuser WRITE setFreeForSuperuser NOTIFY freeForSuperuserChanged);
public:
    explicit MilkyDevice(QObject *parent = 0);
    MilkyDevice(_m_dev_struct* const device, QObject *parent = 0);
    MilkyDevice(MilkyDevice const& other, QObject *parent = 0);

    MilkyDevice const& operator=(MilkyDevice const& other);

signals:
    void deviceChanged(QString);
    void mountPointChanged(QString);
    void sizeChanged(int);
    void freeChanged(int);
    void freeForSuperuserChanged(int);

public slots:
    QString getDevice() const;
    QString getMountPoint() const;
    int getSize() const;
    int getFree() const;
    int getFreeForSuperuser() const;

    void setDevice(QString newDevice);
    void setMountPoint(QString newMountPoint);
    void setSize(int newSize);
    void setFree(int newFree);
    void setFreeForSuperuser(int newFreeForSuperuser);

private:
    QString device;
    QString mountPoint;
    int size;
    int free;
    int freeForSuperuser;
};

Q_DECLARE_METATYPE(MilkyDevice)

#endif // MILKYDEVICE_H
