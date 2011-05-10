#include "pandoraeventlistener.h"

#include "pnd_io_evdev.h"
#include <QDebug>

PandoraEventListener::PandoraEventListener(QObject *parent)
    : QThread(parent), _notifier(0)
{}

PandoraEventListener::~PandoraEventListener()
{
    if(_notifier && _notifier->isEnabled())
    {
        _notifier->setEnabled(false);
        emit isActiveChanged(false);
    }
    if(_notifier)
    {
        delete _notifier;
    }
    pnd_evdev_close(pnd_evdev_dpads);
}

void PandoraEventListener::run()
{
    if(pnd_evdev_open(pnd_evdev_dpads))
    {
        _notifier = new QSocketNotifier(pnd_evdev_get_fd(pnd_evdev_dpads), QSocketNotifier::Read);
        connect(_notifier, SIGNAL(activated(int)), this, SLOT(readEvent()));
        emit isActiveChanged(true);
    }
    else
        qWarning() << "Warning: Failed to locate D-Pad controls. "
                "This means that only keyboard controls can be used.";
    exec();
}

bool PandoraEventListener::isActive()
{
    return _notifier && _notifier->isEnabled();
}

void PandoraEventListener::readEvent()
{
    pnd_evdev_catchup(0);
    emit newEvent(pnd_evdev_dpad_state(pnd_evdev_dpads));
}
