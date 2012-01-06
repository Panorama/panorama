#include "systeminformationattached.h"

#include <QStringList>
#include <QTimer>
#include <QFile>
#include <QTextStream>

extern "C"
{
#include <sys/statvfs.h>
}

class SystemInformationAttachedPrivate
{
    PANORAMA_DECLARE_PUBLIC(SystemInformationAttached)
public:
    SystemInformationAttachedPrivate();
    void updateMem();
    void updateCpu();
    void updateSd();
    void updateBattery();

    QTimer timer;
    long long lastUsedCpuTime;
    long long lastCpuTime;
    int cpu;
    int usedCpu;
    int ram;
    int usedRam;
    int swap;
    int usedSwap;
    int sd1;
    int usedSd1;
    int sd2;
    int usedSd2;
    int battery;
};

SystemInformationAttached::SystemInformationAttached(QObject *parent) :
        QObject(parent)
{
    PANORAMA_INITIALIZE(SystemInformationAttached);

    update();
    connect(&priv->timer, SIGNAL(timeout()), this, SLOT(update()));
    priv->timer.setInterval(1000);
    priv->timer.start();
}

SystemInformationAttached::~SystemInformationAttached()
{
    PANORAMA_UNINITIALIZE(SystemInformationAttached);
}

void SystemInformationAttached::update()
{
    PANORAMA_PRIVATE(SystemInformationAttached);
    priv->updateCpu();
    priv->updateMem();
    priv->updateSd();
    priv->updateBattery();
}

int SystemInformationAttached::cpu() const
{
    PANORAMA_PRIVATE(const SystemInformationAttached);
    return priv->cpu;
}

int SystemInformationAttached::usedCpu() const
{
    PANORAMA_PRIVATE(const SystemInformationAttached);
    return priv->usedCpu;
}

int SystemInformationAttached::ram() const
{
    PANORAMA_PRIVATE(const SystemInformationAttached);
    return priv->ram;
}

int SystemInformationAttached::usedRam() const
{
    PANORAMA_PRIVATE(const SystemInformationAttached);
    return priv->usedRam;
}

int SystemInformationAttached::swap() const
{
    PANORAMA_PRIVATE(const SystemInformationAttached);
    return priv->swap;
}

int SystemInformationAttached::usedSwap() const
{
    PANORAMA_PRIVATE(const SystemInformationAttached);
    return priv->usedSwap;
}

int SystemInformationAttached::sd1() const
{
    PANORAMA_PRIVATE(const SystemInformationAttached);
    return priv->sd1;
}

int SystemInformationAttached::usedSd1() const
{
    PANORAMA_PRIVATE(const SystemInformationAttached);
    return priv->usedSd1;
}

int SystemInformationAttached::sd2() const
{
    PANORAMA_PRIVATE(const SystemInformationAttached);
    return priv->sd2;
}

int SystemInformationAttached::usedSd2() const
{
    PANORAMA_PRIVATE(const SystemInformationAttached);
    return priv->usedSd2;
}

int SystemInformationAttached::battery() const
{
    PANORAMA_PRIVATE(const SystemInformationAttached);
    return priv->battery;
}

void SystemInformationAttachedPrivate::updateCpu()
{
    PANORAMA_PUBLIC(SystemInformationAttached);
    QFile stat("/proc/stat");
    if(!stat.open(QFile::Text | QFile::ReadOnly | QFile::Unbuffered))
        return;
    QString line = QTextStream(&stat).readLine();
    stat.close();
    if(!line.isNull() && line.startsWith("cpu  "))
    {
        QStringList components = line.right(line.length() - 5).split(" ");
        bool ok;
        int user, nice, system, idle;
        user   = components[0].toInt(&ok, 10);
        if(!ok) return;
        nice   = components[1].toInt(&ok, 10);
        if(!ok) return;
        system = components[2].toInt(&ok, 10);
        if(!ok) return;
        idle   = components[3].toInt(&ok, 10);
        if(!ok) return;


        int tmp = user + system + nice + idle;
        if(lastCpuTime)
        {
            int value = tmp - lastCpuTime;
            if(cpu != value)
            {
                cpu = value;
                emit pub->cpuUpdated(cpu);
            }
        }
        lastCpuTime = tmp;

        tmp = user + system;
        if(lastUsedCpuTime)
        {
            int value = tmp - lastUsedCpuTime;
            if(usedCpu != value)
            {
                usedCpu = value;
                emit pub->usedCpuUpdated(usedCpu);
            }
        }
        lastUsedCpuTime = tmp;
    }
}

void SystemInformationAttachedPrivate::updateSd()
{
    PANORAMA_PUBLIC(SystemInformationAttached);
    struct statvfs fs;
    int newSd1(0), newUsedSd1(0), newSd2(0), newUsedSd2(0);

    QFile mounts("/proc/mounts");
    if(!mounts.open(QFile::Text | QFile::ReadOnly | QFile::Unbuffered))
        return;

    QTextStream in(&mounts);

    while(!(newSd1 && newSd2))
    {
        QString line = in.readLine();

        if(line.isNull())
            break;

        QStringList parts = line.split(' ');

        if(parts.length() < 2)
            continue;

        const QString &source = parts[0];

        //Note that the mount point will have e.g. spaces escaped as \040:
        const QString &mountPoint = parts[1];

        if(source == "/dev/mmcblk0p1" && statvfs(mountPoint.toLocal8Bit(), &fs) > -1)
        {
            newSd1 = int(fs.f_blocks * fs.f_frsize / (1024L * 1024L));
            newUsedSd1 = int((fs.f_blocks - fs.f_bfree) * fs.f_frsize / (1024L * 1024L));
        }
        else if(source == "/dev/mmcblk1p1" && statvfs(mountPoint.toLocal8Bit(), &fs) > -1)
        {
            newSd2 = int(fs.f_blocks * fs.f_frsize / (1024L * 1024L));
            newUsedSd2 = int((fs.f_blocks - fs.f_bfree) * fs.f_frsize / (1024L * 1024L));
        }
    }
    mounts.close();

    if(sd1 != newSd1)
    {
        sd1 = newSd1;
        emit pub->sd1Updated(sd1);
    }
    if(usedSd1 != newUsedSd1)
    {
        usedSd1 = newUsedSd1;
        emit pub->usedSd1Updated(usedSd1);
    }

    if(sd2 != newSd2)
    {
        sd2 = newSd2;
        emit pub->sd2Updated(sd2);
    }
    if(usedSd2 != newUsedSd2)
    {
        usedSd2 = newUsedSd2;
        emit pub->usedSd2Updated(usedSd2);
    }
}

void SystemInformationAttachedPrivate::updateMem()
{
    PANORAMA_PUBLIC(SystemInformationAttached);
    int newUsedRam, newUsedSwap;
    int freeRam = 0, bufferRam = 0, cacheRam = 0, freeSwap = 0;
    int newRam = 0, newSwap = 0;
    unsigned long long value;
    bool ok;
    QString line;
    QFile meminfo("/proc/meminfo");

    if(!meminfo.open(QFile::Text | QFile::ReadOnly | QFile::Unbuffered))
        return;

    QTextStream memIn(&meminfo);

    while(!(newRam && freeRam && bufferRam && cacheRam && newSwap && freeSwap))
    {
        line = memIn.readLine();
        if(line.isNull())
            break;

        //TODO: optimize this:
        value = line.split(QRegExp("\\s+"))[1].toInt(&ok, 10);
        if(ok)
        {
            if(line.startsWith("MemTotal:"))
                newRam = int(value / 1024L);
            else if(line.startsWith("MemFree:"))
                freeRam = int(value / 1024L);
            else if(line.startsWith("Buffers:"))
                bufferRam = int(value / 1024L);
            else if(line.startsWith("Cached:"))
                cacheRam = int(value / 1024L);
            else if(line.startsWith("SwapTotal:"))
                newSwap = int(value / 1024L);
            else if(line.startsWith("SwapFree:"))
                freeSwap = int(value / 1024L);
        }
    }
    meminfo.close();

    newUsedSwap = newSwap - freeSwap;
    newUsedRam = newRam - freeRam - bufferRam - cacheRam;

    if(ram != newRam)
    {
        ram = newRam;
        emit pub->ramUpdated(ram);
    }

    if(usedRam != newUsedRam)
    {
        usedRam = newUsedRam;
        emit pub->usedRamUpdated(usedRam);
    }

    if(swap != newSwap)
    {
        swap = newSwap;
        emit pub->swapUpdated(swap);
    }

    if(usedSwap != newUsedSwap)
    {
        usedSwap = newUsedSwap;
        emit pub->usedSwapUpdated(usedSwap);
    }
}

void SystemInformationAttachedPrivate::updateBattery() {
    PANORAMA_PUBLIC(SystemInformationAttached);
    QFile stat("/sys/class/power_supply/bq27500-0/capacity");
    if(!stat.open(QFile::Text | QFile::ReadOnly | QFile::Unbuffered))
        return;
    QString line = QTextStream(&stat).readLine();
    stat.close();
    if(!line.isNull())
    {
        bool ok = false;
        int batteryCapacity = line.toInt(&ok);
        if(ok) {
            battery = batteryCapacity;
            emit pub->batteryUpdated(battery);
        }
    }
}

SystemInformationAttachedPrivate::SystemInformationAttachedPrivate()
{
    ram = 0;
    usedRam = 0;
    swap = 0;
    usedSwap = 0;
    sd1 = 0;
    usedSd1 = 0;
    sd2 = 0;
    usedSd2 = 0;

    lastCpuTime = 0;
    lastUsedCpuTime = 0;

    battery = 0;
}

