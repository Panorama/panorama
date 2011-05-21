#include "pandoraeventlistener.h"

#include <QSocketNotifier>
#include <QDebug>

#include "pnd_io_evdev.h"

class PandoraEventListenerPrivate
{
    PANORAMA_DECLARE_PUBLIC(PandoraEventListener)
public:
    explicit PandoraEventListenerPrivate();
    ~PandoraEventListenerPrivate();
    QSocketNotifier *notifier;
};

PandoraEventListener::PandoraEventListener(QObject *parent)
    : QThread(parent)
{
    PANORAMA_INITIALIZE(PandoraEventListener);
}

PandoraEventListener::~PandoraEventListener()
{
    pnd_evdev_close(pnd_evdev_dpads);
    PANORAMA_UNINITIALIZE(PandoraEventListener);
}

void PandoraEventListener::run()
{
    PANORAMA_PRIVATE(PandoraEventListener);
    if(pnd_evdev_open(pnd_evdev_dpads))
    {
        priv->notifier = new QSocketNotifier(pnd_evdev_get_fd(pnd_evdev_dpads), QSocketNotifier::Read);
        connect(priv->notifier, SIGNAL(activated(int)), this, SLOT(readEvent()));
        emit isActiveChanged(true);
    }
    else
        qWarning() << "Warning: Failed to locate D-Pad controls. "
                "This means that only keyboard controls can be used.";
    exec();
}

bool PandoraEventListener::isActive()
{
    PANORAMA_PRIVATE(PandoraEventListener);
    return priv->notifier && priv->notifier->isEnabled();
}

void PandoraEventListener::readEvent()
{
    pnd_evdev_catchup(0);
    emit newEvent(pnd_evdev_dpad_state(pnd_evdev_dpads));
}

PandoraEventListenerPrivate::PandoraEventListenerPrivate()
{
    notifier = 0;
}
PandoraEventListenerPrivate::~PandoraEventListenerPrivate()
{
    PANORAMA_PUBLIC(PandoraEventListener);
    if(notifier && notifier->isEnabled())
    {
        notifier->setEnabled(false);
        emit pub->isActiveChanged(false);
    }
    if(notifier)
    {
        delete notifier;
    }
}
