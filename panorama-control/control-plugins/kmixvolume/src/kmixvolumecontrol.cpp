#include "kmixvolumecontrol.h"
#include "concept.h"
#include <QDBusMessage>

KMixVolumeControl::KMixVolumeControl(QObject *parent) :
    Control(parent), _dbus(QDBusConnection::sessionBus())
{
    _concepts += dynamic_cast<Concept *>(new Bounded(0, 100));
    _concepts += dynamic_cast<Concept *>(Ordered::ints);
    _concepts += dynamic_cast<Concept *>(Enumerable::ints);
    _concepts += dynamic_cast<Concept *>(Showable::trivial);
    _concepts += dynamic_cast<Concept *>(Integral::trivial);
    connect(this, SIGNAL(valueChanged(QVariant)), this, SLOT(changeVolume(QVariant)));

    _timer.setInterval(1000);
    connect(&_timer, SIGNAL(timeout()), this, SLOT(refreshVolume()));
    _timer.start();
}

KMixVolumeControl::~KMixVolumeControl()
{
    foreach(Concept *const concept, _concepts)
    {
        delete concept;
    }
}

QList<Concept *> KMixVolumeControl::concepts() const
{
    return _concepts;
}

QString KMixVolumeControl::name() const
{
    return "Master volume";
}

void KMixVolumeControl::changeVolume(QVariant volume)
{
    QDBusMessage message = QDBusMessage::createMethodCall("org.kde.kmix", "/Mixer0", "org.kde.KMix", "setMasterVolume");
    QList<QVariant> arguments;
    arguments << volume.toInt() + 1;
    message.setArguments(arguments);
    _dbus.call(message, QDBus::NoBlock);
}

void KMixVolumeControl::refreshVolume()
{
    QDBusMessage message = QDBusMessage::createMethodCall("org.kde.kmix", "/Mixer0", "org.kde.KMix", "masterVolume");
    QDBusMessage reply = _dbus.call(message, QDBus::Block);
    int newVolume = reply.arguments().at(0).toInt();
    if(newVolume != value().toInt())
    {
        setValue(newVolume);
    }
}
