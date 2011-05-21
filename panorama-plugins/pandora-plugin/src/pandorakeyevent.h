#ifndef PANDORAKEYEVENT_H
#define PANDORAKEYEVENT_H

#include <QObject>
#include <QEvent>
#include <QKeyEvent>
#include "qdeclarative.h"

class PandoraKeyEvent : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int key READ key)
    Q_PROPERTY(QString text READ text)
    Q_PROPERTY(int modifiers READ modifiers)
    Q_PROPERTY(bool isAutoRepeat READ isAutoRepeat)
    Q_PROPERTY(int count READ count)
    Q_PROPERTY(bool accepted READ isAccepted WRITE setAccepted)
public:
    PandoraKeyEvent(QEvent::Type type, int key,
                    Qt::KeyboardModifiers modifiers,
                    const QString &text=QString(),
                    bool autorep = false, ushort count = 1,
                    QObject *parent = 0);
    PandoraKeyEvent(const QKeyEvent &event, QObject *parent = 0); //Not explicit; allow auto conversion from QKeyEvent

    int key() const;
    QString text() const;
    int modifiers() const;
    bool isAutoRepeat() const;
    int count() const;

    bool isAccepted() const;
    void setAccepted(bool accepted);

private:
    QKeyEvent _event;
};

QML_DECLARE_TYPE(PandoraKeyEvent);

#endif // PANDORAKEYEVENT_H
