#ifndef PANDORAATTACHED_H
#define PANDORAATTACHED_H

#include <QObject>
#include "pandoraeventsource.h"

class PandoraAttached : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool controlsActive READ controlsActive NOTIFY controlsActiveUpdated)
public:
    explicit PandoraAttached(QObject *parent = 0);
    bool controlsActive() const;

signals:
    void pressed(const QVariant &event);
    void released(const QVariant &event);
    void controlsActiveUpdated(const bool state);

protected slots:
    void keyPressed(const PandoraKeyEvent &event);
    void keyReleased(const PandoraKeyEvent &event);

    void setActive(bool const value);

private:
    bool active;
};

#endif // PANDORAATTACHED_H
