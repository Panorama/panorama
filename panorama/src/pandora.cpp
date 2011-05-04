#include "pandora.h"
#include "pandoraeventsource.h"

Pandora::Pandora(QObject *parent)
    : QObject(parent)
{}

PandoraAttached *Pandora::qmlAttachedProperties(QObject *)
{
    return &_attached;
}

PandoraAttached Pandora::_attached;
