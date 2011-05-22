#ifndef CONCEPT_H
#define CONCEPT_H

#include <QVariant>
#include <QString>

class Concept
{
public:
    Concept(unsigned int id) : id(id) {}
    const unsigned int id;
};

template<typename A, typename B>
class Either
{
public:
    Either(const A &a) : a(a), isLeft(true) {}
    Either(const B &b) : b(b), isLeft(false) {}
    const A a;
    const B b;
    const bool isLeft;
};

class Bounded : public Concept
{
public:
    static const unsigned int ID = 0xda785952;
    Bounded(QVariant min, QVariant max)
        : Concept(ID), minBound(min), maxBound(max) {}
    const QVariant minBound;
    const QVariant maxBound;
};

class Ordered : public Concept
{
public:
    enum Ordering
    {
        LessThan,
        Equal,
        GreaterThan
    };
    static const unsigned int ID = 0xb5ab790a;
    explicit Ordered(Ordering (* const compare)(const QVariant &, const QVariant &))
        : Concept(ID), compare(compare) {}
    Ordering (* const compare)(const QVariant &, const QVariant &);

    static Ordered *const ints;
    static Ordered *const doubles;
    static Ordered *const floats;
    static Ordered *const strings;
};

//Use explicit vtables instead of virtual calls, to discourage closures.
//XXX Good idea?

class Enumerable : public Concept
{
public:
    static const unsigned int ID = 0x5ca3891c;
    Enumerable(QVariant (* const successor)(const QVariant &), QVariant (* const predecessor)(const QVariant &))
        : Concept(ID), successor(successor), predecessor(predecessor) {}
    QVariant (* const successor)(const QVariant &);
    QVariant (* const predecessor)(const QVariant &);

    static Enumerable *const ints;
};

class Showable : public Concept
{
public:
    static const unsigned int ID = 0x85be83da;
    explicit Showable(QString (* const toString)(const QVariant &))
        : Concept(ID), toString(toString) {}
    QString (* const toString)(const QVariant &);

    static Showable *const trivial;
};

class Readable : public Concept
{
public:
    static const unsigned int ID = 0x5d4a16aa;
    explicit Readable(Either<QVariant, QString> (* const fromString)(const QString &))
        : Concept(ID), fromString(fromString) {}
    Either<QVariant, QString> (* const fromString)(const QString &);
};

class Integral : public Concept
{
public:
    static const unsigned int ID = 0xc6ea2eca;
    explicit Integral(int (* const toInt)(const QVariant &))
        : Concept(ID), toInt(toInt) {}
    int (* const toInt)(const QVariant &);

    static Integral *const trivial;
};

#endif // CONCEPT_H
