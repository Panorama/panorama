#include "kmixvolumeplugin.h"
#include "kmixvolumecontrol.h"

KMixVolumePlugin::KMixVolumePlugin()
{
    _controls << new KMixVolumeControl();
}

QSet<Control *> KMixVolumePlugin::controls() const
{
    return _controls;
}

KMixVolumePlugin::~KMixVolumePlugin()
{
    foreach(Control *const control, _controls)
    {
        delete control;
    }
}
