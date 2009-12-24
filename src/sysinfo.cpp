#include "sysinfo.h"

int Sysinfo::getUsedRam()
{
    updateSys();
    return int((_sys.totalram - _sys.freeram) * (unsigned long)(_sys.mem_unit) / (1024 * 1024));
}

int Sysinfo::getTotalRam()
{
    updateSys();
    return int(_sys.totalram * (unsigned long)(_sys.mem_unit) / (1024 * 1024));
}

int Sysinfo::getUsedSwap()
{
    updateSys();
    return int((_sys.totalswap - _sys.freeswap) * (unsigned long)(_sys.mem_unit) / (1024 * 1024));
}

int Sysinfo::getTotalSwap()
{
    updateSys();
    return int(_sys.totalswap * (unsigned long)(_sys.mem_unit) / (1024 * 1024));
}

int Sysinfo::getSd1Usage()
{
    updateFs();
    return (_fs1.f_blocks - _fs1.f_bfree) * _fs1.f_frsize / (1024 * 1024);
}

int Sysinfo::getSd1Size()
{
    updateFs();
    return _fs1.f_blocks * _fs1.f_frsize / (1024 * 1024);
}

int Sysinfo::getSd2Usage()
{
    updateFs();
    return (_fs2.f_blocks - _fs2.f_bfree) * _fs1.f_frsize / (1024 * 1024);
}

int Sysinfo::getSd2Size()
{
    updateFs();
    return _fs2.f_blocks * _fs2.f_frsize / (1024 * 1024);
}

void Sysinfo::updateSys()
{
    sysinfo(&_sys);
}

void Sysinfo::updateFs()
{
    statvfs("/mnt/sd1", &_fs1);
    statvfs("/mnt/sd1", &_fs2);
}

struct sysinfo Sysinfo::_sys;
struct statvfs Sysinfo::_fs1;
struct statvfs Sysinfo::_fs2;
