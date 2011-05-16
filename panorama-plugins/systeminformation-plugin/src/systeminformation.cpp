#include "systeminformation.h"
#include <QStringList>

#include <QTimer>
#include <QFile>
#include <QTextStream>

extern "C"
{
#include <sys/statvfs.h>
}

class SystemInformationPrivate
{
    PANORAMA_DECLARE_PUBLIC(SystemInformation)
public:
    SystemInformationPrivate();
    void updateMem();
    void updateCpu();
    void updateSd();

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
};

SystemInformation::SystemInformation(QObject *parent) :
        QObject(parent)
{
    PANORAMA_INITIALIZE(SystemInformation);

    update();
    connect(&priv->timer, SIGNAL(timeout()), this, SLOT(update()));
    priv->timer.setInterval(1000);
    priv->timer.start();
}

SystemInformation::~SystemInformation()
{
    PANORAMA_UNINITIALIZE(SystemInformation);
}

void SystemInformation::update()
{
    PANORAMA_PRIVATE(SystemInformation);
    priv->updateCpu();
    priv->updateMem();
    priv->updateSd();
}

int SystemInformation::cpu() const
{
    PANORAMA_PRIVATE(const SystemInformation);
    return priv->cpu;
}

int SystemInformation::usedCpu() const
{
    PANORAMA_PRIVATE(const SystemInformation);
    return priv->usedCpu;
}

int SystemInformation::ram() const
{
    PANORAMA_PRIVATE(const SystemInformation);
    return priv->ram;
}

int SystemInformation::usedRam() const
{
    PANORAMA_PRIVATE(const SystemInformation);
    return priv->usedRam;
}

int SystemInformation::swap() const
{
    PANORAMA_PRIVATE(const SystemInformation);
    return priv->swap;
}

int SystemInformation::usedSwap() const
{
    PANORAMA_PRIVATE(const SystemInformation);
    return priv->usedSwap;
}

int SystemInformation::sd1() const
{
    PANORAMA_PRIVATE(const SystemInformation);
    return priv->sd1;
}

int SystemInformation::usedSd1() const
{
    PANORAMA_PRIVATE(const SystemInformation);
    return priv->usedSd1;
}

int SystemInformation::sd2() const
{
    PANORAMA_PRIVATE(const SystemInformation);
    return priv->sd2;
}

int SystemInformation::usedSd2() const
{
    PANORAMA_PRIVATE(const SystemInformation);
    return priv->usedSd2;
}

void SystemInformationPrivate::updateCpu()
{
    PANORAMA_PUBLIC(SystemInformation);
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

void SystemInformationPrivate::updateSd()
{
    PANORAMA_PUBLIC(SystemInformation);
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

void SystemInformationPrivate::updateMem()
{
    PANORAMA_PUBLIC(SystemInformation);
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

SystemInformationPrivate::SystemInformationPrivate()
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
}

