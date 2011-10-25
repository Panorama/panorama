#ifndef MILKYPLUGIN_H
#define MILKYPLUGIN_H

#include <qdeclarative.h>
#include <QDeclarativeExtensionPlugin>

class MilkyPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    void registerTypes(const char *uri);
};

#endif // MILKYPLUGIN_H
