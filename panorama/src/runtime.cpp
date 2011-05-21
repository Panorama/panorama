#include "runtime.h"

Runtime::Runtime(QObject *parent) :
        QObject(parent), _isActiveWindow(false), _fullscreen(false)
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

bool Runtime::fullscreen() const
{
    return _fullscreen;
}

void Runtime::setFullscreen(bool fullscreen)
{
    if(_fullscreen != fullscreen)
    {
        _fullscreen = fullscreen;
        emit fullscreenChanged(fullscreen);
    }
}
