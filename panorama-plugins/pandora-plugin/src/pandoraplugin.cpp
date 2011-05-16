#include "pandoraplugin.h"
#include "pandora.h"

void PandoraPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<Pandora>(uri,1,0,"Pandora");
}

Q_EXPORT_PLUGIN(Pandora);
