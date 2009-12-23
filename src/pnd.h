#ifndef PND_H
#define PND_H

#include <QString>

struct Pnd
{
    QString uid;
    QString preview;
    int clockspeed;

    bool operator ==(const Pnd &that) const;
};

#endif // PND_H
