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

    QSet<Control *> controls() const;
private:
    QSet<Control *> _controls;
};

#endif // KMIXVOLUMEPLUGIN_H
