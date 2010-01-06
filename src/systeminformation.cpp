#include "systeminformation.h"

SystemInformation::SystemInformation(QObject *parent) :
    QObject(parent)
{
    _ram = 0;
    _usedRam = 0;
    _swap = 0;
    _usedSwap = 0;
    _sd1 = 0;
    _usedSd1 = 0;
    _sd2 = 0;
    _usedSd2 = 0;

    _lastCpuTime = 0;
    _lastUsedCpuTime = 0;

    update();
    connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer.setInterval(1000);
    _timer.start();
}

void SystemInformation::update()
{
    updateCpu();
    updateMem();
    updateSd();
}

void SystemInformation::updateCpu()
{
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
        if(_lastCpuTime)
        {
            int value = tmp - _lastCpuTime;
            if(_cpu != value)
            {
                _cpu = value;
                emit cpuUpdated(_cpu);
            }
        }
        _lastCpuTime = tmp;

        tmp = user + system;
        if(_lastUsedCpuTime)
        {
            int value = tmp - _lastUsedCpuTime;
            if(_usedCpu != value)
            {
                _usedCpu = value;
                emit usedCpuUpdated(_usedCpu);
            }
        }
        _lastUsedCpuTime = tmp;
    }
}

void SystemInformation::updateSd()
{
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

        QString source(parts[0]);

        //Note that the mount point will have e.g. spaces escaped as \040:
        QString mountPoint(parts[1]);

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

    if(_sd1 != newSd1)
    {
        _sd1 = newSd1;
        emit sd1Updated(_sd1);
    }
    if(_usedSd1 != newUsedSd1)
    {
        _usedSd1 = newUsedSd1;
        emit usedSd1Updated(_usedSd1);
    }

    if(_sd2 != newSd2)
    {
        _sd2 = newSd2;
        emit sd2Updated(_sd2);
    }
    if(_usedSd2 != newUsedSd2)
    {
        _usedSd2 = newUsedSd2;
        emit usedSd2Updated(_usedSd2);
    }
}

void SystemInformation::updateMem()
{
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

    if(_ram != newRam)
    {
        _ram = newRam;
        emit ramUpdated(_ram);
    }

    if(_usedRam != newUsedRam)
    {
        _usedRam = newUsedRam;
        emit usedRamUpdated(_usedRam);
    }

    if(_swap != newSwap)
    {
        _swap = newSwap;
        emit swapUpdated(_swap);
    }

    if(_usedSwap != newUsedSwap)
    {
        _usedSwap = newUsedSwap;
        emit usedSwapUpdated(_usedSwap);
    }
}

QML_DEFINE_TYPE(Panorama,1,0,SystemInformation,SystemInformation);
