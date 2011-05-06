#ifndef PANDORAEVENTSOURCE_H
#define PANDORAEVENTSOURCE_H

#include <QObject>
#include <QTimer>
#include <QSocketNotifier>
#include <QKeyEvent>
#include <QThread>

class PandoraEventListener : public QThread
{
    Q_OBJECT
    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged)
public:
    explicit PandoraEventListener();
    ~PandoraEventListener();

    bool isActive();

signals:
    void isActiveChanged(const bool value);
    void newEvent(const int state);

protected:
    void run();

private slots:
    void readEvent();

private:
    QSocketNotifier *_notifier;
};

class PandoraEventSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged)
public:
    explicit PandoraEventSource(QObject *parent = 0);

    bool isActive();

signals:
    void isActiveChanged(const bool value);
    void keyPressed(const QKeyEvent &event);
    void keyReleased(const QKeyEvent &event);

private slots:
    void handleEvent(const int dpadState);

private:
    inline void emitKeyEvent(const int key, const bool press);
    inline void testKey(const int prevState, const int currentState, const int mask, const int keyToEmit);
    QObject *_receiver;
    int _prevState;
    bool _hasReceivedInput;
    static PandoraEventListener *_eventListener;
};

#endif // PANDORAEVENTSOURCE_H
