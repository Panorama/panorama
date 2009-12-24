#include "panoramaui.h"

PanoramaUI::PanoramaUI(QmlGraphicsItem *parent) :
    QmlGraphicsItem(parent)
{
    setWidth(UI_WIDTH);
    setHeight(UI_HEIGHT);
    setX(0);
    setY(0);
    setClip(true);
}

void PanoramaUI::setName(const QString &value)
{
    _name = value;
}

QString PanoramaUI::name() const
{
    return _name;
}

void PanoramaUI::setDescription(const QString &value)
{
    _description = value;
}

QString PanoramaUI::description() const
{
    return _description;
}

void PanoramaUI::setAuthor(const QString &value)
{
    _author = value;
}

QString PanoramaUI::author() const
{
    return _author;
}

QString PanoramaUI::settingsKey() const
{
    return _settingsKey;
}

void PanoramaUI::setSettingsKey(const QString &value)
{
    _settingsKey = QString(value).replace('\n', ' ');
}

QVariant PanoramaUI::applications() const
{
    return _apps;
}

void PanoramaUI::setApplicationsSource(QAbstractItemModel *value)
{
    QVariant n(QVariant::fromValue((QObject *) value));
    if(_apps != n)
        _apps = n;
}

void PanoramaUI::setSettingsSource(QHash<QString, QHash<QString, QString> *> *value)
{
    _settings = value;
}

void PanoramaUI::execute(const QString &sha1)
{
    QString cleanCommand(AppAccumulator::getExecLine(sha1));
    if(!cleanCommand.isEmpty())
    {
        cleanCommand.remove(QRegExp("%\\w"));
        QProcess::startDetached(cleanCommand);
    }
}

void PanoramaUI::applicationDataChanged()
{
    emit applicationsUpdated(_apps);
}

void PanoramaUI::loaded()
{
    emit load();
}

QVariant PanoramaUI::_apps;
QHash<QString, QHash<QString, QString> *> *PanoramaUI::_settings = 0;

//Makes this type available in QML
QML_DEFINE_TYPE(Panorama,1,0,PanoramaUI,PanoramaUI);
