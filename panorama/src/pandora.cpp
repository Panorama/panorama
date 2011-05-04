#include "pandora.h"
#include "pandoraeventsource.h"

Pandora::Pandora(QObject *parent)
    : QObject(parent)
{
    connect(&_pandoraEventSource, SIGNAL(isActiveChanged(bool)),
            this, SIGNAL(controlsActiveUpdated(bool)));
    connect(&_pandoraEventSource, SIGNAL(pressed(int)),
            this, SIGNAL(pressed(int)));
    connect(&_pandoraEventSource, SIGNAL(released(int)),
            this, SIGNAL(released(int)));
}

bool Pandora::controlsActive()
{
    return _pandoraEventSource.isActive();
}

PandoraEventSource Pandora::_pandoraEventSource;
