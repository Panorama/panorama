#ifndef PANDORA_H
#define PANDORA_H

#include <QObject>
#include "pandoraeventsource.h"

class Pandora : public QObject
{
    Q_OBJECT
    Q_ENUMS(Key)
    Q_PROPERTY(bool controlsActive READ controlsActive NOTIFY controlsActiveUpdated)
public:
    explicit Pandora(QObject *parent = 0);

    bool controlsActive();

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

signals:
    void controlsActiveUpdated(const bool state);
    void pressed(const int key);
    void released(const int key);
private:
    static PandoraEventSource _pandoraEventSource;
};

#endif // PANDORA_H
