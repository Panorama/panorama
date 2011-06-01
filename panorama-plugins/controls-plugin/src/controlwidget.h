#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QDeclarativeItem>
#include "control.h"

class ControlWidget : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(Control * control READ control WRITE setControl NOTIFY controlChanged)
public:
    explicit ControlWidget(QObject *parent = 0);

    Control *control() const;
    void setControl(Control *control);
signals:
    void controlChanged(Control *control);
};

#endif // CONTROLWIDGET_H
