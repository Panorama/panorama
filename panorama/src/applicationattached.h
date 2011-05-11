#ifndef APPLICATIONATTACHED_H
#define APPLICATIONATTACHED_H

#include <QObject>
#include <QVariant>
#include <QString>

class ApplicationsAttached : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant list READ list NOTIFY listChanged)
public:
    explicit ApplicationsAttached(QObject *parent = 0);

    QVariant list() const;
    Q_INVOKABLE void execute(const QString &id) const;
signals:
    void listChanged();
};

#endif // APPLICATIONATTACHED_H
