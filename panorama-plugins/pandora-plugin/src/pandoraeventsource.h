#ifndef PANDORAEVENTSOURCE_H
#define PANDORAEVENTSOURCE_H

#include "panoramainternal.h"

#include <QObject>
#include "pandorakeyevent.h"

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
    void keyPressed(const PandoraKeyEvent &event);
    void keyReleased(const PandoraKeyEvent &event);

protected slots:
    void handleEvent(const int dpadState);
#ifdef POLTERGEIST
    void generateEvent();
#endif
};

#endif // PANDORAEVENTSOURCE_H
