#ifndef PANDORA_H
#define PANDORA_H

#include <QObject>

class Pandora : public QObject
{
    Q_OBJECT
    Q_ENUMS(Key)
public:
    explicit Pandora(QObject *parent = 0);

    enum Key { //Codes are set apart from Qt::Key values
        DPadLeft      = 0x01200012, //For every key, key & 0xfe000000 must == 0
        DPadUp        = 0x01200013,
        DPadRight     = 0x01200014,
        DPadDown      = 0x01200015,
        ButtonX       = 0x01300000,
        ButtonY       = 0x01300001,
        ButtonA       = 0x01300002,
        ButtonB       = 0x01300003,
        TriggerL      = 0x01200059,
        TriggerR      = 0x01200060,
        ButtonStart   = 0x01200055,
        ButtonSelect  = 0x01200058,
        ButtonPandora = 0x0120010a
    };
};

#endif // PANDORA_H
