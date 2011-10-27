#include "pandorakeyevent.h"

PandoraKeyEvent::PandoraKeyEvent(QEvent::Type type, int key,
                                 Qt::KeyboardModifiers modifiers,
                                 const QString &text,
                                 bool autorep, ushort count,
                                 QObject *parent)
                                     : QObject(parent), _event(type, key, modifiers, text, autorep, count)
{
    _event.setAccepted(false);
}

PandoraKeyEvent::PandoraKeyEvent(const QKeyEvent &event, QObject *parent)
    : QObject(parent), _event(event)
{
    _event.setAccepted(false);
}

int PandoraKeyEvent::key() const
{
    return _event.key();
}

QString PandoraKeyEvent::text() const
{
    return _event.text();
}

int PandoraKeyEvent::modifiers() const
{
    return _event.modifiers();
}

bool PandoraKeyEvent::isAutoRepeat() const
{
    return _event.isAutoRepeat();
}

int PandoraKeyEvent::count() const
{
    return _event.count();
}

bool PandoraKeyEvent::isAccepted() const
{
    return _event.isAccepted();
}

void PandoraKeyEvent::setAccepted(bool accepted)
{
    _event.setAccepted(accepted);
}
