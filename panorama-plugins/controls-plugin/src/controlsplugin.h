#ifndef CONTROLSPLUGIN_H
#define CONTROLSPLUGIN_H

#include <qdeclarative.h>
#include <QDeclarativeExtensionPlugin>

class ControlsPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    void registerTypes(const char *uri);
};

#endif // CONTROLSPLUGIN_H
