#include "pandoraeventsource.h"

#include <QCoreApplication>
#include <QDebug>

#include "pandora.h"
#include "pnd_io_evdev.h"
#include "pandoraeventlistener.h"

#ifdef POLTERGEIST
#include <QTimer>
#endif

class PandoraEventSourcePrivate
{
    PANORAMA_DECLARE_PUBLIC(PandoraEventSource)
public:
    explicit PandoraEventSourcePrivate();
    inline void emitKeyEvent(const int key, const bool press);
    inline void testKey(const int prevState, const int currentState, const int mask, const int keyToEmit);

    int prevState;
    bool hasReceivedInput;

#ifdef POLTERGEIST
    QTimer poltergeistTimer;
#endif
};

PandoraEventListener *_pandoraeventsource_eventListener;
#define _eventListener _pandoraeventsource_eventListener

PandoraEventSource::PandoraEventSource(QObject *parent) :
        QObject(parent)
{
    PANORAMA_INITIALIZE(PandoraEventSource);
    if(!_eventListener)
    {
        _eventListener = new PandoraEventListener();
        _eventListener->start();
    }
    connect(_eventListener, SIGNAL(isActiveChanged(bool)),
            this, SIGNAL(isActiveChanged(bool)));
    connect(_eventListener, SIGNAL(newEvent(int)), this, SLOT(handleEvent(int)));
#ifdef POLTERGEIST
    priv->poltergeistTimer.setInterval(1000);
    priv->poltergeistTimer.setSingleShot(false);
    connect(&priv->poltergeistTimer, SIGNAL(timeout()),
            this, SLOT(generateEvent()));
    priv->poltergeistTimer.start();
    emit isActiveChanged(true);
#endif
}

PandoraEventSource::~PandoraEventSource()
{
    PANORAMA_UNINITIALIZE(PandoraEventSource);
}

bool PandoraEventSource::isActive()
{
#ifdef POLTERGEIST
    return true;
#else
    return _eventListener->isActive();
#endif
}

void PandoraEventSource::handleEvent(const int dpadState)
{
    PANORAMA_PRIVATE(PandoraEventSource);
    if(!priv->hasReceivedInput)
    {
        priv->prevState = dpadState;
        priv->hasReceivedInput = true;
        return;
    }

    int prevState = priv->prevState;

    if(dpadState == prevState)
        return;

    priv->testKey(prevState, dpadState, pnd_evdev_left, Pandora::DPadLeft);
    priv->testKey(prevState, dpadState, pnd_evdev_right, Pandora::DPadRight);
    priv->testKey(prevState, dpadState, pnd_evdev_up, Pandora::DPadUp);
    priv->testKey(prevState, dpadState, pnd_evdev_down, Pandora::DPadDown);
    priv->testKey(prevState, dpadState, pnd_evdev_x, Pandora::ButtonX);
    priv->testKey(prevState, dpadState, pnd_evdev_y, Pandora::ButtonY);
    priv->testKey(prevState, dpadState, pnd_evdev_a, Pandora::ButtonA);
    priv->testKey(prevState, dpadState, pnd_evdev_b, Pandora::ButtonB);
    priv->testKey(prevState, dpadState, pnd_evdev_start, Pandora::ButtonStart);
    priv->testKey(prevState, dpadState, pnd_evdev_select, Pandora::ButtonSelect);
    priv->testKey(prevState, dpadState, pnd_evdev_pandora, Pandora::ButtonPandora);
    priv->testKey(prevState, dpadState, pnd_evdev_ltrigger, Pandora::TriggerL);
    priv->testKey(prevState, dpadState, pnd_evdev_rtrigger, Pandora::TriggerR);

    priv->prevState = dpadState;
}

#ifdef POLTERGEIST
void PandoraEventSource::generateEvent()
{
    PANORAMA_PRIVATE(PandoraEventSource);
    handleEvent(priv->prevState ^ (1 << (qrand() % 12)));
}
#endif

void PandoraEventSourcePrivate::emitKeyEvent(const int key, const bool press)
{
    PANORAMA_PUBLIC(PandoraEventSource);
    if(press)
        emit pub->keyPressed(QKeyEvent(QKeyEvent::KeyPress, key, Qt::NoModifier));
    else
        emit pub->keyReleased(QKeyEvent(QKeyEvent::KeyRelease, key, Qt::NoModifier));
}

void PandoraEventSourcePrivate::testKey(const int prevState, const int currentState, const int mask, const int keyToEmit)
{
    if((currentState ^ prevState) & mask) //Key changed
        emitKeyEvent(keyToEmit, currentState & mask);
}

PandoraEventSourcePrivate::PandoraEventSourcePrivate()
{
    prevState = 0;
    hasReceivedInput = false;
}
