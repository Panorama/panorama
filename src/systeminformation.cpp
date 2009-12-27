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

    update();
    connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer.setInterval(1000);
    _timer.start();
}

void SystemInformation::update()
{
    int newUsedRam, newUsedSwap;
    int freeRam = 0, bufferRam = 0, cacheRam = 0, freeSwap = 0;
    int newRam = 0, newSwap = 0;
    QFile meminfo("/proc/meminfo");

    if(!meminfo.open(QFile::Text | QFile::ReadOnly | QFile::Unbuffered))
        return;

    QTextStream memIn(&meminfo);
    QString line;
    unsigned long long value;
    bool ok;

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

    struct statvfs fs;
    int tmp;
    statvfs("/mnt/sd1", &fs);

    tmp = int(fs.f_blocks * fs.f_frsize / (1024L * 1024L));
    if(_sd1 != tmp)
    {
        _sd1 = tmp;
        emit sd1Updated(_sd1);
    }

    tmp = int((fs.f_blocks - fs.f_bfree) * fs.f_frsize / (1024L * 1024L));
    if(_usedSd1 != tmp)
    {
        _usedSd1 = tmp;
        emit usedSd1Updated(_usedSd1);
    }

    statvfs("/mnt/sd2", &fs);

    tmp = int(fs.f_blocks * fs.f_frsize / (1024L * 1024L));
    if(_sd2 != tmp)
    {
        _sd2 = tmp;
        emit sd2Updated(_sd2);
    }

    tmp = int((fs.f_blocks - fs.f_bfree) * fs.f_frsize / (1024L * 1024L));
    if(_usedSd2 != tmp)
    {
        _usedSd2 = tmp;
        emit usedSd2Updated(_usedSd2);
    }
}
QML_DEFINE_TYPE(Panorama,1,0,SystemInformation,SystemInformation)
