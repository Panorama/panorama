#include "pnd.h"

bool Pnd::operator ==(const Pnd &that) const
{
    return this->uid == that.uid;
}
