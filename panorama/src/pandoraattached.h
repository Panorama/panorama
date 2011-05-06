#ifndef PANDORAATTACHED_H
#define PANDORAATTACHED_H

#include <QObject>
#include <QKeyEvent>
#include "pandoraeventsource.h"

class PandoraAttached : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool controlsActive READ controlsActive NOTIFY controlsActiveUpdated)
public:
    explicit PandoraAttached(QObject *parent = 0);
    bool controlsActive();

signals:
    void pressed(const QKeyEvent &event);
    void released(const QKeyEvent &event);
    void controlsActiveUpdated(const bool state);

private:
    static PandoraEventSource _pandoraEventSource;
};

#endif // PANDORAATTACHED_H
