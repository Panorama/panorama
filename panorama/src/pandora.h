#ifndef PANDORA_H
#define PANDORA_H

#include <QObject>
#include <qdeclarative.h>
#include <QKeyEvent>
#include "pandoraeventsource.h"
#include "pandoraattached.h"

class Pandora : public QObject
{
    Q_OBJECT
    Q_ENUMS(Key)
public:
    explicit Pandora(QObject *parent = 0);

    enum Key {
        DPadLeft      = 0x00000001,
        DPadUp        = 0x00000002,
        DPadRight     = 0x00000003,
        DPadDown      = 0x00000004,
        ButtonX       = 0x00000005,
        ButtonY       = 0x00000006,
        ButtonA       = 0x00000007,
        ButtonB       = 0x00000008,
        TriggerL      = 0x00000009,
        TriggerR      = 0x0000000a,
        ButtonStart   = 0x0000000b,
        ButtonSelect  = 0x0000000c,
        ButtonPandora = 0x0000000d
    };

    static PandoraAttached *qmlAttachedProperties(QObject *parent);
};

QML_DECLARE_TYPEINFO(Pandora, QML_HAS_ATTACHED_PROPERTIES)

#endif // PANDORA_H
