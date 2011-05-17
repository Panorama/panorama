#ifndef TEXTFILEPLUGIN_H
#define TEXTFILEPLUGIN_H

#include <qdeclarative.h>
#include <QDeclarativeExtensionPlugin>

class TextFilePlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    void registerTypes(const char *uri);
};

#endif // TEXTFILEPLUGIN_H
