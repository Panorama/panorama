#ifndef SYSINFO_H
#define SYSINFO_H

extern "C" {
    #include <sys/sysinfo.h>
    #include <sys/statvfs.h>
}

class Sysinfo
{
public:
    static int getUsedRam();
    static int getTotalRam();
    static int getUsedSwap();
    static int getTotalSwap();

    static int getSd1Usage();
    static int getSd1Size();
    static int getSd2Usage();
    static int getSd2Size();

private:
    Sysinfo() {};
    Sysinfo(const Sysinfo&);
    Sysinfo& operator=(const Sysinfo&);

    static void updateSys();
    static void updateFs();

    static struct sysinfo _sys;
    static struct statvfs _fs1;
    static struct statvfs _fs2;
};

#endif // SYSINFO_H
