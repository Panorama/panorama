#include "runtime.h"

Runtime::Runtime(QObject *parent) :
        QObject(parent), isActiveWindow(false)
{
}

bool Runtime::getIsActiveWindow()
{
    return isActiveWindow;
}

void Runtime::setIsActiveWindow(bool const value)
{
    isActiveWindow = value;
    emit isActiveWindowChanged(value);
}
