#include "pandoraattached.h"

PandoraAttached::PandoraAttached(QObject *parent) :
    QObject(parent)
{
    connect(&_pandoraEventSource, SIGNAL(isActiveChanged(bool)),
            this, SIGNAL(controlsActiveUpdated(bool)));
    connect(&_pandoraEventSource, SIGNAL(keyPressed(QKeyEvent)),
            this, SIGNAL(pressed(QKeyEvent)));
    connect(&_pandoraEventSource, SIGNAL(keyReleased(QKeyEvent)),
            this, SIGNAL(released(QKeyEvent)));
}

bool PandoraAttached::controlsActive()
{
    return _pandoraEventSource.isActive();
}
