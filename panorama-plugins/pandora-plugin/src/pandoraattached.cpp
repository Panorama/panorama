#include "pandoraattached.h"
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include <QDebug>

PandoraEventSource *_pandoraattached_pandoraEventSource;
#define _pandoraEventSource _pandoraattached_pandoraEventSource

PandoraAttached::PandoraAttached(QObject *parent) :
    QObject(parent), active(true)
{
    if(!_pandoraEventSource)
        _pandoraEventSource = new PandoraEventSource();
    connect(_pandoraEventSource, SIGNAL(isActiveChanged(bool)),
            this, SIGNAL(controlsActiveUpdated(bool)));
    connect(_pandoraEventSource, SIGNAL(keyPressed(PandoraKeyEvent)),
            this, SLOT(keyPressed(PandoraKeyEvent)));
    connect(_pandoraEventSource, SIGNAL(keyReleased(PandoraKeyEvent)),
            this, SLOT(keyReleased(PandoraKeyEvent)));

    QDeclarativeContext* context = QDeclarativeEngine::contextForObject(parent);
    if(context)
    {
        QVariant runtime = context->contextProperty("runtime");
        if(!runtime.isNull())
        {
            QObject* runtimeObject = qvariant_cast<QObject*>(runtime);
            if(runtimeObject)
            {
                connect(runtimeObject, SIGNAL(isActiveWindowChanged(bool)), this, SLOT(setActive(bool)));
            }
        }
    }
}

bool PandoraAttached::controlsActive() const
{
    return _pandoraEventSource->isActive();
}

void PandoraAttached::keyPressed(const PandoraKeyEvent &event)
{
    if(active)
        emit pressed(QVariant::fromValue((QObject *) &event));
}

void PandoraAttached::keyReleased(const PandoraKeyEvent &event)
{
    if(active)
        emit released(QVariant::fromValue((QObject *) &event));
}

void PandoraAttached::setActive(bool const value)
{
    active = value;
}
