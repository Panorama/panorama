#ifndef KMIXVOLUMEPLUGIN_H
#define KMIXVOLUMEPLUGIN_H

#include "controlplugin.h"
#include <QObject>

class KMixVolumePlugin : public QObject, ControlPlugin
{
    Q_OBJECT
    Q_INTERFACES(ControlPlugin)
public:
    KMixVolumePlugin();
    ~KMixVolumePlugin();

    QList<Control *> controls() const;
private:
    QList<Control *> _controls;
};

#endif // KMIXVOLUMEPLUGIN_H
