#ifndef PANDORAATTACHED_H
#define PANDORAATTACHED_H

#include "panoramainternal.h"

#include <QObject>
#include "pandoraeventsource.h"

class PandoraAttachedPrivate;

class PandoraAttached : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool controlsActive READ controlsActive NOTIFY controlsActiveUpdated)
    PANORAMA_DECLARE_PRIVATE(PandoraAttached)
public:
    explicit PandoraAttached(QObject *parent = 0);
    ~PandoraAttached();
    bool controlsActive() const;

signals:
    void pressed(const QVariant &event);
    void released(const QVariant &event);
    void controlsActiveUpdated(const bool state);

protected slots:
    void keyPressed(const PandoraKeyEvent &event);
    void keyReleased(const PandoraKeyEvent &event);
    void setActive(bool value);
};

#endif // PANDORAATTACHED_H
