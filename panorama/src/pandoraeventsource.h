#ifndef PANDORAEVENTSOURCE_H
#define PANDORAEVENTSOURCE_H

#include <QObject>
#include <QTimer>
#include <QSocketNotifier>

class PandoraEventSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged)
public:
    explicit PandoraEventSource(QObject *parent = 0);
    ~PandoraEventSource();

    bool isActive();

signals:
    void isActiveChanged(const bool value);
    void keyPressed(const int key);
    void keyReleased(const int key);

private slots:
    void handleEvents();

private:
    inline void emitKeyEvent(const int key, const bool press);
    inline void testKey(const int prevState, const int currentState, const int mask, const int keyToEmit);
    QObject *_receiver;
    QSocketNotifier *_notifier;
    int _prevState;
    bool _init;
};

#endif // PANDORAEVENTSOURCE_H
