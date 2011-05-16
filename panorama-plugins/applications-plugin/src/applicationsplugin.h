#ifndef APPLICATIONSPLUGIN_H
#define APPLICATIONSPLUGIN_H

#include <qdeclarative.h>
#include <QDeclarativeExtensionPlugin>

class ApplicationsPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    void registerTypes(const char *uri);
};

#endif // APPLICATIONSPLUGIN_H
