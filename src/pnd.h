#ifndef PND_H
#define PND_H

#include <QString>

/**
 * Represents a PND file
 */
struct Pnd
{
    /** This PND's uid */
    QString uid;

    /** The path to this PND's preview picture */
    QString preview;

    /**
     * The clockspeed at which the application contained within this PND
     * should run
     */
    int clockspeed;

    /** Compares one Pnd instance to another */
    bool operator ==(const Pnd &that) const;
};

#endif // PND_H
