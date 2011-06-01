#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QSet>
#include "concept.h"

class Control : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged)
public:
    Control(QObject *parent = 0);
    Control(const QVariant &value, QObject *parent = 0);
    virtual ~Control() {}
    virtual QSet<Concept *> concepts() const = 0;

    QVariant value() const;
    void setValue(const QVariant &value);

    virtual QString name() const = 0;
    virtual QString description() const { return QString(); }
    virtual QString icon() const { return QString(); }
signals:
    void valueChanged(QVariant value);
private:
    QVariant _value;
};

#endif // CONTROL_H
