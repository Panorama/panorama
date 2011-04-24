#include "pandoraeventsource.h"

#include <QCoreApplication>
#include <QKeyEvent>
#include <QDebug>

#include "pnd_io_ioctl.h"
#include "pnd_io_evdev.h"
#include "pandora.h"

PandoraEventSource::PandoraEventSource(QObject *receiver, QObject *parent) :
        QObject(parent), _receiver(receiver), _prevState(0), _init(false)
{
    //TODO Find better way of polling events, maybe hook into th event queue?
    connect(&_timer, SIGNAL(timeout()), this, SLOT(handleEvents()));
    _timer.setInterval(10);
    _timer.setSingleShot(false);

    if(pnd_evdev_open(pnd_evdev_dpads))
        _timer.start();
    else
        qWarning() << "Warning: Failed to locate D-Pad controls. "
                "This means that only keyboard controls can be used.";
}

PandoraEventSource::~PandoraEventSource()
{
    if(_timer.isActive())
    {
        _timer.stop();
        pnd_evdev_close(pnd_evdev_dpads);
    }
}

bool PandoraEventSource::isActive()
{
    return _timer.isActive();
}

void PandoraEventSource::handleEvents()
{
    pnd_evdev_catchup(0); //1 == Don't do this asynchronously

    int dpadState = pnd_evdev_dpad_state(pnd_evdev_dpads);
    //int dpadState = _prevState ^ (1 << (qrand() % 12)); //Toggle random key
    if(!_init)
    {
        _prevState = dpadState;
        _init = true;
        return;
    }

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

    _prevState = dpadState;
}

void PandoraEventSource::emitKeyEvent(const int key, const bool press) const
{
    //TODO: Modifier keys + Pandora buttons = ??
    QCoreApplication::postEvent(_receiver, new QKeyEvent(press ? QEvent::KeyPress : QEvent::KeyRelease, key, Qt::NoModifier));
}

void PandoraEventSource::testKey(const int prevState, const int currentState, const int mask, const int keyToEmit) const
{
    if((currentState ^ prevState) & mask) //Key changed
        emitKeyEvent(keyToEmit, currentState & mask);
}
