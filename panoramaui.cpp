#include "panoramaui.h"

PanoramaUI::PanoramaUI(QmlGraphicsItem *parent) :
    QmlGraphicsItem(parent)
{
    setWidth(800);
    setHeight(480);

    _name = "";
    _description = "";
    _author = "";
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
    _settingsKey = value;
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

void PanoramaUI::setSetting(const QString &key, const QString &value)
{
    if(_settings)
    {
        if(!_settings->contains(_settingsKey))
            _settings->insert(_settingsKey, new QHash<QString, QString>);
        _settings->value(_settingsKey)->insert(key, value);
    }
}

QString PanoramaUI::setting(const QString &key)
{
    if(_settings && _settings->contains(_settingsKey) && _settings->value(_settingsKey)->contains(key))
        return _settings->value(_settingsKey)->value(key);
    else
        return QString();
}

void PanoramaUI::setSharedSetting(const QString &section, const QString &key, const QString &value)
{
    if(_settings)
    {
        if(!_settings->contains(section))
            _settings->insert(section, new QHash<QString, QString>);
        _settings->value(section)->insert(key, value);
    }
}

QString PanoramaUI::sharedSetting(const QString &section, const QString &key)
{
    if(_settings && _settings->contains(section) && _settings->value(section)->contains(key))
        return _settings->value(section)->value(key);
    else
        return QString();
}

void PanoramaUI::execute(const QString &sha1)
{
    QString cleanCommand(AppAccumulator::getExec(sha1));
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

QVariant PanoramaUI::_apps = QVariant();
QHash<QString, QHash<QString, QString> *> *PanoramaUI::_settings = 0;

//Makes this type available in QML
QML_DEFINE_TYPE(Panorama,1,0,PanoramaUI,PanoramaUI)
