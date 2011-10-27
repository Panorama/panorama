#ifndef MILKYREPOSITORY_H
#define MILKYREPOSITORY_H

#include <QObject>
#include <QDateTime>
#include "milky/milky.h"

class MilkyRepository : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ getName NOTIFY nameChanged);
    Q_PROPERTY(QString url READ getUrl NOTIFY urlChanged);
    Q_PROPERTY(QString merge READ getMerge NOTIFY mergeChanged);
    Q_PROPERTY(QDateTime timestamp READ getTimestamp NOTIFY timestampChanged);

public:
    explicit MilkyRepository(pnd_repo* repository, QObject *parent = 0);

    QString getName();
    QString getUrl();
    QString getMerge();
    QDateTime getTimestamp();

signals:
    void nameChanged(QString newName);
    void urlChanged(QString newUrl);
    void mergeChanged(QString newMerge);
    void timestampChanged(QDateTime newTimestamp);

public slots:

private:
    QString name;
    QString url;
    QString merge;
    QDateTime timestamp;
};

#endif // MILKYREPOSITORY_H
