#include "milkyplugin.h"
#include "milkymodel.h"

void MilkyPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<MilkyModel>(uri, 1, 0, "Milky");
    qmlRegisterType<MilkyListener>(uri, 1, 0, "MilkyListener");
    qmlRegisterType<MilkyEvents>(uri, 1, 0, "MilkyEvents");
}

Q_EXPORT_PLUGIN2(milky,MilkyPlugin);
