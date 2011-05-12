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
            this, SLOT(keyPressed(PandoraKeyEvent)));
    connect(_pandoraEventSource, SIGNAL(keyReleased(PandoraKeyEvent)),
            this, SLOT(keyReleased(PandoraKeyEvent)));
}

bool PandoraAttached::controlsActive() const
{
    return _pandoraEventSource->isActive();
}

void PandoraAttached::keyPressed(const PandoraKeyEvent &event)
{
    emit pressed(QVariant::fromValue((QObject *) &event));
}

void PandoraAttached::keyReleased(const PandoraKeyEvent &event)
{
    emit released(QVariant::fromValue((QObject *) &event));
}
