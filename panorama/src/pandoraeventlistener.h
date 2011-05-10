#ifndef PANDORAEVENTLISTENER_H
#define PANDORAEVENTLISTENER_H

#include <QSocketNotifier>
#include <QThread>

class PandoraEventListener : public QThread
{
    Q_OBJECT
    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged)
public:
    explicit PandoraEventListener(QObject *parent = 0);
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

#endif // PANDORAEVENTLISTENER_H
