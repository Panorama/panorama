#ifndef SYSTEMINFORMATIONATTACHED_H
#define SYSTEMINFORMATIONATTACHED_H

#include "panoramainternal.h"

#include <QObject>

class SystemInformationAttachedPrivate;

class SystemInformationAttached : public QObject
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
    Q_PROPERTY(int battery  READ battery    NOTIFY batteryUpdated)
    PANORAMA_DECLARE_PRIVATE(SystemInformationAttached)
public:
    explicit SystemInformationAttached(QObject *parent = 0);
    ~SystemInformationAttached();

    /**
     * Returns a number representing the maximum CPU time for any given
     * time span. Use this as a fraction with "usedCpu" to get the CPU-usage in
     * percent.
     */
    int cpu() const;

    /** Returns the used CPU time for any given time span. */
    int usedCpu() const;

    /** Returns the amount of RAM installed in the system, in mebibytes */
    int ram() const;

    /** Returns the amount of RAM that is used by applications, in mebibytes */
    int usedRam() const;

    /** Returns the amount of swap that is available on this system in MiB */
    int swap() const;

    /** Returns the amount of swap that is currently being used in MiB */
    int usedSwap() const;

    /** Returns the size of the first SD card in mebibytes */
    int sd1() const;

    /** Returns the amount of space that is used up on SD 1 in mebibytes */
    int usedSd1() const;

    /** Returns the size of the second SD card in mebibytes */
    int sd2() const;

    /** Returns the amount of space that is used up on SD 2 in mebibytes */
    int usedSd2() const;

    /** Returns the amount of remaining battery charge in percents */
    int battery() const;

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

    /** This value has changed */
    void batteryUpdated(int value);

protected slots:
    void update();

};

#endif // SYSTEMINFORMATIONATTACHED_H
