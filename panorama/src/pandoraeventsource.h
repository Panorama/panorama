#ifndef PANDORAEVENTSOURCE_H
#define PANDORAEVENTSOURCE_H

#include "panoramainternal.h"

#include <QObject>
#include <QKeyEvent>

class PandoraEventSourcePrivate;

class PandoraEventSource : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged)
    PANORAMA_DECLARE_PRIVATE(PandoraEventSource)
public:
    explicit PandoraEventSource(QObject *parent = 0);
    ~PandoraEventSource();

    bool isActive();

signals:
    void isActiveChanged(const bool value);
    void keyPressed(const QKeyEvent &event);
    void keyReleased(const QKeyEvent &event);

protected slots:
    void handleEvent(const int dpadState);
};

#endif // PANDORAEVENTSOURCE_H
