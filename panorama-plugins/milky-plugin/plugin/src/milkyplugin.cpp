#include "milkyplugin.h"
#include "milkymodel.h"
#include "milkypackage.h"

void MilkyPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<MilkyModel>(uri, 1, 0, "Milky");
    qmlRegisterType<MilkyListener>(uri, 1, 0, "MilkyListener");
    qmlRegisterType<MilkyEvents>(uri, 1, 0, "MilkyEvents");
    qmlRegisterType<MilkyPackage>(uri, 1, 0, "MilkyPackage");
}

Q_EXPORT_PLUGIN2(milky,MilkyPlugin);
