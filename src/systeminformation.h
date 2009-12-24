#ifndef SYSTEMINFORMATION_H
#define SYSTEMINFORMATION_H

#include <QObject>
#include <qml.h>
#include <QTimer>

#include "sysinfo.h"

class SystemInformation : public QObject
{
Q_OBJECT
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
    int ram() const { return _ram; }
    int usedRam() const { return _ram; }
    int swap() const { return _ram; }
    int usedSwap() const { return _ram; }
    int sd1() const { return _ram; }
    int usedSd1() const { return _ram; }
    int sd2() const { return _ram; }
    int usedSd2() const { return _ram; }

signals:
    void ramUpdated(int value);
    void usedRamUpdated(int value);
    void swapUpdated(int value);
    void usedSwapUpdated(int value);
    void sd1Updated(int value);
    void usedSd1Updated(int value);
    void sd2Updated(int value);
    void usedSd2Updated(int value);

private slots:
    void update();

private:
    QTimer _timer;

    int _ram;
    int _usedRam;
    int _swap;
    int _usedSwap;
    int _sd1;
    int _usedSd1;
    int _sd2;
    int _usedSd2;
};

QML_DECLARE_TYPE(SystemInformation)

#endif // SYSTEMINFORMATION_H
