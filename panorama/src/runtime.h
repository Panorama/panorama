#ifndef RUNTIME_H
#define RUNTIME_H

#include <QObject>
#include <QtDeclarative>

class Runtime : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isActiveWindow READ getIsActiveWindow WRITE setIsActiveWindow NOTIFY isActiveWindowChanged)

public:
    explicit Runtime(QObject *parent = 0);


    bool getIsActiveWindow();
    void setIsActiveWindow(bool const value);

signals:
    void isActiveWindowChanged(bool const value);

public slots:    

private:
    bool isActiveWindow;

};

#endif // RUNTIME_H
