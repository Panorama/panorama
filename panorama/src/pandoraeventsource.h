#ifndef PANDORAEVENTSOURCE_H
#define PANDORAEVENTSOURCE_H

#include <QObject>
#include <QTimer>
#include <QSocketNotifier>

class PandoraEventSource : public QObject
{
    Q_OBJECT
public:
    explicit PandoraEventSource(QObject *receiver, QObject *parent = 0);
    ~PandoraEventSource();

    bool isActive();

private slots:
    void handleEvents();

private:
    inline void emitKeyEvent(const int key, const bool press) const;
    inline void testKey(const int prevState, const int currentState, const int mask, const int keyToEmit) const;
    QObject *_receiver;
    QSocketNotifier *_notifier;
    int _prevState;
    bool _init;
};

#endif // PANDORAEVENTSOURCE_H
