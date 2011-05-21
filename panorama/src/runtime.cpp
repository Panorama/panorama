#include "runtime.h"

Runtime::Runtime(QObject *parent) :
        QObject(parent), _isActiveWindow(false)
{
}

bool Runtime::isActiveWindow() const
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

void Runtime::setFullscreen(bool fullscreen)
{
    emit fullscreenRequested(fullscreen);
}
