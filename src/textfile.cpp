#include "textfile.h"

TextFile::TextFile(QObject*parent) :
    QObject(parent)
{}

QString TextFile::source() const
{
    return _source;
}

void TextFile::setSource(const QString &value)
{
    if(_source != value)
    {
        _source = value;
        emit sourceChanged(_source);
        loadFile(_source);
    }
}

QString TextFile::data() const
{
    return _data;
}

void TextFile::loadFile(const QString &source)
{
    //XXX: this does not work for all themes!
    QString path(qmlContext(this)->baseUrl().toLocalFile());
    path.resize(path.lastIndexOf("/") + 1);
    path.append(source);
    QFile file(path);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Could not open file" << source;
        return;
    }
    QTextStream in(&file);
    _data = in.readAll();
    file.close();

    emit dataChanged(_data);
}

QML_DEFINE_TYPE(Panorama,1,0,TextFile,TextFile);
