#include "textfileplugin.h"
#include "textfile.h"

void TextFilePlugin::registerTypes(const char *uri)
{
    qmlRegisterType<TextFile>(uri, 1, 0, "TextFile");
}

Q_EXPORT_PLUGIN2(textfile,TextFilePlugin);
