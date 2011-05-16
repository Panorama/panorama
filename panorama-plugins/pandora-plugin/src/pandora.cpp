#include "pandora.h"
#include "pandoraeventsource.h"

Pandora::Pandora(QObject *parent)
    : QObject(parent)
{}

PandoraAttached *Pandora::qmlAttachedProperties(QObject *parent)
{
    return new PandoraAttached(parent);
}
