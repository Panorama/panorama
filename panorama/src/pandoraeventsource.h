#ifndef PANDORAEVENTSOURCE_H
#define PANDORAEVENTSOURCE_H

#include <QObject>
#include <QKeyEvent>

#include "pandoraeventlistener.h"

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
