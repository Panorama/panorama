#include "runtime.h"

Runtime::Runtime(QObject *parent) :
        QObject(parent), _isActiveWindow(false)
{
}

bool Runtime::getIsActiveWindow()
{
    return _isActiveWindow;
}

void Runtime::setIsActiveWindow(bool const value)
{
    if(_isActiveWindow != value)
    {
        _isActiveWindow = value;
        emit isActiveWindowChanged(value);
    }
}
