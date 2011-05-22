#ifndef CONTROLPLUGIN_H
#define CONTROLPLUGIN_H

#include <QList>
#include "control.h"

class ControlPlugin
{
public:
    virtual ~ControlPlugin() = 0;
    virtual QList<Control *> controls() const = 0;
};
Q_DECLARE_INTERFACE(ControlPlugin, "org.panorama.controlplugin/1.0")

#endif // CONTROLPLUGIN_H
