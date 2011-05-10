#include "pandoraeventsource.h"

#include <QCoreApplication>
#include <QDebug>

#include "pandora.h"
#include "pnd_io_evdev.h"

PandoraEventSource::PandoraEventSource(QObject *parent) :
        QObject(parent), _prevState(0),
        _hasReceivedInput(false)
{
    if(!_eventListener)
    {
        _eventListener = new PandoraEventListener();
        _eventListener->start();
    }
    connect(_eventListener, SIGNAL(isActiveChanged(bool)),
            this, SIGNAL(isActiveChanged(bool)));
    connect(_eventListener, SIGNAL(newEvent(int)), this, SLOT(handleEvent(int)));
}

bool PandoraEventSource::isActive()
{
    return _eventListener->isActive();
}

void PandoraEventSource::handleEvent(const int dpadState)
{
    if(!_hasReceivedInput)
    {
        _prevState = dpadState;
        _hasReceivedInput = true;
        return;
    }

    if(dpadState == _prevState)
        return;

    testKey(_prevState, dpadState, pnd_evdev_left, Pandora::DPadLeft);
    testKey(_prevState, dpadState, pnd_evdev_right, Pandora::DPadRight);
    testKey(_prevState, dpadState, pnd_evdev_up, Pandora::DPadUp);
    testKey(_prevState, dpadState, pnd_evdev_down, Pandora::DPadDown);
    testKey(_prevState, dpadState, pnd_evdev_x, Pandora::ButtonX);
    testKey(_prevState, dpadState, pnd_evdev_y, Pandora::ButtonY);
    testKey(_prevState, dpadState, pnd_evdev_a, Pandora::ButtonA);
    testKey(_prevState, dpadState, pnd_evdev_b, Pandora::ButtonB);
    testKey(_prevState, dpadState, pnd_evdev_start, Pandora::ButtonStart);
    testKey(_prevState, dpadState, pnd_evdev_select, Pandora::ButtonSelect);
    testKey(_prevState, dpadState, pnd_evdev_pandora, Pandora::ButtonPandora);
    testKey(_prevState, dpadState, pnd_evdev_ltrigger, Pandora::TriggerL);
    testKey(_prevState, dpadState, pnd_evdev_rtrigger, Pandora::TriggerR);

    _prevState = dpadState;
}

void PandoraEventSource::emitKeyEvent(const int key, const bool press)
{
    if(press)
        emit keyPressed(QKeyEvent(QKeyEvent::KeyPress, key, Qt::NoModifier));
    else
        emit keyReleased(QKeyEvent(QKeyEvent::KeyRelease, key, Qt::NoModifier));
}

void PandoraEventSource::testKey(const int prevState, const int currentState, const int mask, const int keyToEmit)
{
    if((currentState ^ prevState) & mask) //Key changed
        emitKeyEvent(keyToEmit, currentState & mask);
}

PandoraEventListener *PandoraEventSource::_eventListener(0);
