#ifndef PNDSCANNER_H
#define PNDSCANNER_H

#include <QObject>
#include <QDebug>
#include <pnd_conf.h>
#include <pnd_apps.h>
#include <pnd_container.h>
#include <pnd_discovery.h>
#include "pnd.h"

class PndScanner : public QObject
{
Q_OBJECT
public:
    explicit PndScanner(QObject *parent = 0);
    QList<Pnd> scanPnds();
};

#endif // PNDSCANNER_H
