#ifndef KMIXVOLUMECONTROL_H
#define KMIXVOLUMECONTROL_H

#include "control.h"
#include <QDBusConnection>
#include <QTimer>

class KMixVolumeControl : public Control
{
    Q_OBJECT
public:
    explicit KMixVolumeControl(QObject *parent = 0);
    ~KMixVolumeControl();
    QList<Concept *> concepts() const;
    QString name() const;

private slots:
    void changeVolume(QVariant volume);
    void refreshVolume();

private:
    QList<Concept *> _concepts;
    QDBusConnection _dbus;
    QTimer _timer;
};

#endif // KMIXVOLUMECONTROL_H
