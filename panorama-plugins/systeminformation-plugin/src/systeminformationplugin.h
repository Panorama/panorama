#ifndef SYSTEMINFORMATIONPLUGIN_H
#define SYSTEMINFORMATIONPLUGIN_H

#include <qdeclarative.h>
#include <QDeclarativeExtensionPlugin>

class SystemInformationPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    void registerTypes(const char *uri);
};

#endif // SYSTEMINFORMATIONPLUGIN_H
