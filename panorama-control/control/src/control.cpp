#include "control.h"

Control::Control(QObject *parent)
    : QObject(parent)
{
}

Control::Control(const QVariant &value, QObject *parent)
    : QObject(parent), _value(value)
{
}
