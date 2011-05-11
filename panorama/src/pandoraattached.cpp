#include "pandoraattached.h"

PandoraEventSource *_pandoraattached_pandoraEventSource;
#define _pandoraEventSource _pandoraattached_pandoraEventSource

PandoraAttached::PandoraAttached(QObject *parent) :
    QObject(parent)
{
    if(!_pandoraEventSource)
        _pandoraEventSource = new PandoraEventSource();
    connect(_pandoraEventSource, SIGNAL(isActiveChanged(bool)),
            this, SIGNAL(controlsActiveUpdated(bool)));
    connect(_pandoraEventSource, SIGNAL(keyPressed(PandoraKeyEvent)),
            this, SIGNAL(pressed(PandoraKeyEvent)));
    connect(_pandoraEventSource, SIGNAL(keyReleased(PandoraKeyEvent)),
            this, SIGNAL(released(PandoraKeyEvent)));
}

bool PandoraAttached::controlsActive() const
{
    return _pandoraEventSource->isActive();
}
