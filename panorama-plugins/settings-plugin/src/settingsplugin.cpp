#include "settingsplugin.h"
#include "setting.h"

void SettingsPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Setting>(uri,1,0,"Setting");
}

Q_EXPORT_PLUGIN2(settings,SettingsPlugin);
