#include "textfile.h"

class TextFilePrivate
{
    PANORAMA_DECLARE_PUBLIC(TextFile)
public:
    void loadFile(const QString &source);
    QString source;
    QString data;
};

TextFile::TextFile(QObject*parent)
    : QObject(parent)
{
    PANORAMA_INITIALIZE(TextFile);
}

TextFile::~TextFile()
{
    PANORAMA_UNINITIALIZE(TextFile);
}

QString TextFile::source() const
{
    PANORAMA_PRIVATE(const TextFile);
    return priv->source;
}

void TextFile::setSource(const QString &value)
{
    PANORAMA_PRIVATE(TextFile);
    if(priv->source != value)
    {
        priv->source = value;
        emit sourceChanged(priv->source);
        priv->loadFile(priv->source);
    }
}

QString TextFile::data() const
{
    PANORAMA_PRIVATE(const TextFile);
    return priv->data;
}

void TextFilePrivate::loadFile(const QString &source)
{
    PANORAMA_PUBLIC(TextFile);
    //XXX: this does not work for all themes!
    QString path(qmlContext(pub)->baseUrl().toLocalFile());
    path.resize(path.lastIndexOf("/") + 1);
    path.append(source);
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Could not open file" << source;
        return;
    }
    QTextStream in(&file);
    data = in.readAll();
    file.close();

    emit pub->dataChanged(data);
}
