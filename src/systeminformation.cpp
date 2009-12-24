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
    int tmp;

    tmp = Sysinfo::getTotalRam();
    if(_ram != tmp)
    {
        _ram = tmp;
        emit ramUpdated(_ram);
    }

    tmp = Sysinfo::getUsedRam();
    if(_usedRam != tmp)
    {
        _usedRam = tmp;
        emit usedRamUpdated(_usedRam);
    }

    tmp = Sysinfo::getTotalSwap();
    if(_swap != tmp)
    {
        _swap = tmp;
        emit swapUpdated(_swap);
    }

    tmp = Sysinfo::getUsedSwap();
    if(_usedSwap != tmp)
    {
        _usedSwap = tmp;
        emit usedSwapUpdated(_usedSwap);
    }

    tmp = Sysinfo::getSd1Size();
    if(_sd1 != tmp)
    {
        _sd1 = tmp;
        emit sd1Updated(_sd1);
    }

    tmp = Sysinfo::getSd1Usage();
    if(_usedSd1 != tmp)
    {
        _usedSd1 = tmp;
        emit usedSd1Updated(_usedSd1);
    }

    tmp = Sysinfo::getSd2Size();
    if(_sd2 != tmp)
    {
        _sd2 = tmp;
        emit sd2Updated(_sd2);
    }

    tmp = Sysinfo::getSd2Usage();
    if(_usedSd2 != tmp)
    {
        _usedSd2 = tmp;
        emit usedSd2Updated(_usedSd2);
    }
}
QML_DEFINE_TYPE(Panorama,1,0,SystemInformation,SystemInformation)
