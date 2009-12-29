#ifndef SYSTEMINFORMATION_H
#define SYSTEMINFORMATION_H

#include <QObject>
#include <qml.h>
#include <QTimer>
#include <QFile>
#include <QTextStream>

extern "C"
{
    #include <sys/statvfs.h>
}

class SystemInformation : public QObject
{
Q_OBJECT
Q_PROPERTY(int cpu      READ cpu        NOTIFY cpuUpdated)
Q_PROPERTY(int usedCpu  READ usedCpu    NOTIFY usedCpuUpdated)
Q_PROPERTY(int ram      READ ram        NOTIFY ramUpdated)
Q_PROPERTY(int usedRam  READ usedRam    NOTIFY usedRamUpdated)
Q_PROPERTY(int swap     READ swap       NOTIFY swapUpdated)
Q_PROPERTY(int usedSwap READ usedSwap   NOTIFY usedSwapUpdated)
Q_PROPERTY(int sd1      READ sd1        NOTIFY sd1Updated)
Q_PROPERTY(int usedSd1  READ usedSd1    NOTIFY usedSd1Updated)
Q_PROPERTY(int sd2      READ sd2        NOTIFY sd2Updated)
Q_PROPERTY(int usedSd2  READ usedSd2    NOTIFY usedSd2Updated)
public:
    explicit SystemInformation(QObject *parent = 0);

    /**
     * Returns a number representing the maximum CPU time for any given
     * time span. Use this as a fraction with "usedCpu" to get the CPU-usage in
     * percent.
     */
    int cpu() const
    {
        return _cpu;
    }

    /** Returns the used CPU time for any given time span. */
    int usedCpu() const
    {
        return _usedCpu;
    }

    /** Returns the amount of RAM installed in the system, in mebibytes */
    int ram() const
    {
        return _ram;
    }

    /** Returns the amount of RAM that is used by applications, in mebibytes */
    int usedRam() const
    {
        return _usedRam;
    }

    /** Returns the amount of swap that is available on this system in MiB */
    int swap() const
    {
        return _swap;
    }

    /** Returns the amount of swap that is currently being used in MiB */
    int usedSwap() const
    {
        return _usedSwap;
    }

    /** Returns the size of the first SD card in mebibytes */
    int sd1() const
    {
        return _sd1;
    }

    /** Returns the amount of space that is used up on SD 1 in mebibytes */
    int usedSd1() const
    {
        return _usedSd1;
    }

    /** Returns the size of the second SD card in mebibytes */
    int sd2() const
    {
        return _sd2;
    }

    /** Returns the amount of space that is used up on SD 2 in mebibytes */
    int usedSd2() const
    {
        return _usedSd2;
    }


signals:
    /** This value has changed */
    void cpuUpdated(int value);

    /** This value has changed */
    void usedCpuUpdated(int value);

    /** This value has changed */
    void ramUpdated(int value);

    /** This value has changed */
    void usedRamUpdated(int value);

    /** This value has changed */
    void swapUpdated(int value);

    /** This value has changed */
    void usedSwapUpdated(int value);

    /** This value has changed */
    void sd1Updated(int value);

    /** This value has changed */
    void usedSd1Updated(int value);

    /** This value has changed */
    void sd2Updated(int value);

    /** This value has changed */
    void usedSd2Updated(int value);

private slots:
    void update();

private:
    void updateMem();

    void updateCpu();

    void updateSd();

    QTimer _timer;
    long long _lastUsedCpuTime;
    long long _lastCpuTime;
    int _cpu;
    int _usedCpu;
    int _ram;
    int _usedRam;
    int _swap;
    int _usedSwap;
    int _sd1;
    int _usedSd1;
    int _sd2;
    int _usedSd2;
};

QML_DECLARE_TYPE(SystemInformation);

#endif // SYSTEMINFORMATION_H
