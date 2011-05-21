#include "uiplugin.h"
#include "panoramaui.h"

void UIPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<PanoramaUI>(uri, 1, 0, "PanoramaUI");
}

Q_EXPORT_PLUGIN2(ui,UIPlugin);
