#ifndef SETTINGSPLUGIN_H
#define SETTINGSPLUGIN_H

#include <qdeclarative.h>
#include <QDeclarativeExtensionPlugin>

class SettingsPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    void registerTypes(const char *uri);
};

#endif // SETTINGSPLUGIN_H
