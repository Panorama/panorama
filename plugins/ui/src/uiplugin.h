#ifndef UIPLUGIN_H
#define UIPLUGIN_H

#include <qdeclarative.h>
#include <QDeclarativeExtensionPlugin>

class UIPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    void registerTypes(const char *uri);
};

#endif // UIPLUGIN_H
