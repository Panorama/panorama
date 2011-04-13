#include "panoramaui.h"
#include <qdeclarative.h>

PanoramaUI::PanoramaUI(QDeclarativeItem *parent) :
    QDeclarativeItem(parent)
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

QString PanoramaUI::settingsSection() const
{
    return Setting::defaultSection();
}

void PanoramaUI::setSettingsSection(const QString &value)
{
    Setting::setDefaultSection(value);
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

void PanoramaUI::execute(const QString &sha1)
{
    QString command(AppAccumulator::getExecLine(sha1));
    if(!command.isEmpty())
    {
        Application app(AppAccumulator::getApplication(sha1));

        //Fill in FDF fields
        command.replace("%c", app.name);
        if(!app.icon.isEmpty())
            command.replace("%i", app.icon);
        command.replace("%k", app.relatedFile);
        command.remove(QRegExp("%\\w"));

        QProcess::startDetached(command);
    }
}

void PanoramaUI::propagateApplicationDataChange()
{
    emit applicationsUpdated(_apps);
}

void PanoramaUI::indicateLoadFinished()
{
    emit loaded();
}

QVariant PanoramaUI::_apps;
