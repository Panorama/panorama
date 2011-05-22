#include "milkyplugin.h"
#include "milkymodel.h"

void MilkyPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<MilkyModel>(uri, 1, 0, "Milky");
}

Q_EXPORT_PLUGIN2(milky,MilkyPlugin);
