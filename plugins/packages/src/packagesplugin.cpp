#include "packagesplugin.h"
#include "milkymodel.h"
#include "milkylistener.h"
#include "milkypackage.h"
#include "milkydevice.h"

void MilkyPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<MilkyModel>(uri, 1, 0, "Milky");
    qmlRegisterType<MilkyListener>(uri, 1, 0, "MilkyListener");
    qmlRegisterType<MilkyEvents>(uri, 1, 0, "MilkyEvents");
    qmlRegisterType<MilkyPackage>(uri, 1, 0, "MilkyPackage");
    qmlRegisterType<MilkyDevice>(uri, 1, 0, "MilkyDevice");
}

Q_EXPORT_PLUGIN2(milky,MilkyPlugin);
