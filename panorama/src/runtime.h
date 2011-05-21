#ifndef RUNTIME_H
#define RUNTIME_H

#include <QObject>
#include <QtDeclarative>

class Runtime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isActiveWindow READ isActiveWindow NOTIFY isActiveWindowChanged)
    Q_PROPERTY(bool fullscreen READ fullscreen WRITE setFullscreen NOTIFY fullscreenChanged)

public:
    explicit Runtime(QObject *parent = 0);

    bool isActiveWindow() const;
    void setIsActiveWindow(bool value);

    bool fullscreen() const;
    void setFullscreen(bool value);

signals:
    void isActiveWindowChanged(bool value);
    void fullscreenChanged(bool value);

private:
    bool _isActiveWindow;
    bool _fullscreen;
};

#endif // RUNTIME_H
