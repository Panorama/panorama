#ifndef PANDORAPLUGIN_H
#define PANDORAPLUGIN_H

#include <qdeclarative.h>
#include <QDeclarativeExtensionPlugin>

class PandoraPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    void registerTypes(const char *uri);
};

#endif // PANDORAPLUGIN_H
