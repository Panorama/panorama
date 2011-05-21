#ifndef RUNTIME_H
#define RUNTIME_H

#include <QObject>
#include <QtDeclarative>

class Runtime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isActiveWindow READ isActiveWindow NOTIFY isActiveWindowChanged)

public:
    explicit Runtime(QObject *parent = 0);

    bool isActiveWindow() const;
    void setIsActiveWindow(bool value);

    Q_INVOKABLE void setFullscreen(bool value);

signals:
    void isActiveWindowChanged(bool value);
    void fullscreenRequested(bool value);

private:
    bool _isActiveWindow;
};

#endif // RUNTIME_H
