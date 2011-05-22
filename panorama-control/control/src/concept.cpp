#include "concept.h"

Ordered::Ordering compareInts(const QVariant &a, const QVariant &b) {
    const int ia = a.toInt(), ib = b.toInt();
    if(ia < ib)
        return Ordered::LessThan;
    else if(ia > ib)
        return Ordered::GreaterThan;
    else
        return Ordered::Equal;
}

Ordered::Ordering compareDoubles(const QVariant &a, const QVariant &b) {
    const double ia = a.toDouble(), ib = b.toDouble();
    if(ia < ib)
        return Ordered::LessThan;
    else if(ia > ib)
        return Ordered::GreaterThan;
    else
        return Ordered::Equal;
}

Ordered::Ordering compareFloats(const QVariant &a, const QVariant &b) {
    const float ia = a.toFloat(), ib = b.toFloat();
    if(ia < ib)
        return Ordered::LessThan;
    else if(ia > ib)
        return Ordered::GreaterThan;
    else
        return Ordered::Equal;
}

Ordered::Ordering compareStrings(const QVariant &a, const QVariant &b) {
    const QString ia = a.toString(), ib = b.toString();
    if(ia < ib)
        return Ordered::LessThan;
    else if(ia > ib)
        return Ordered::GreaterThan;
    else
        return Ordered::Equal;
}

Ordered *const Ordered::ints(new Ordered(&compareInts));

Ordered *const Ordered::doubles(new Ordered(&compareDoubles));

Ordered *const Ordered::floats(new Ordered(&compareFloats));

Ordered *const Ordered::strings(new Ordered(&compareStrings));

QVariant nextInt(const QVariant &a)
{
    return a.toInt() + 1;
}

QVariant prevInt(const QVariant &a)
{
    return a.toInt() - 1;
}

Enumerable *const Enumerable::ints(new Enumerable(&nextInt, &prevInt));

QString toStringTrivial(const QVariant &a)
{
    return a.toString();
}

Showable *const Showable::trivial(new Showable(&toStringTrivial));

int toIntTrivial(const QVariant &a)
{
    return a.toInt();
}

Integral *const Integral::trivial(new Integral(&toIntTrivial));
