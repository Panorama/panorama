#include "panoramaui.h"

PanoramaUI::PanoramaUI(QmlGraphicsItem *parent) :
    QmlGraphicsItem(parent)
{
    setWidth(UI_WIDTH);
    setHeight(UI_HEIGHT);
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

void PanoramaUI::setSetting(const QString &key, const QString &value)
{
    if(_settings)
    {
        QString escapedKey(key);
        escapedKey.replace('\n', ' ');

        if(!_settings->contains(_settingsKey))
            _settings->insert(_settingsKey, new QHash<QString, QString>);
        _settings->value(_settingsKey)->insert(escapedKey, value);
    }
}

QString PanoramaUI::setting(const QString &key)
{
    QString escapedKey(key);
    escapedKey.replace('\n', ' ');
    if(_settings && _settings->contains(_settingsKey) && _settings->value(_settingsKey)->contains(escapedKey))
        return _settings->value(_settingsKey)->value(escapedKey);
    else
        return QString();
}

void PanoramaUI::setSharedSetting(const QString &section, const QString &key, const QString &value)
{
    if(_settings)
    {
        QString escapedKey(key);
        escapedKey.replace('\n', ' ');
        QString escapedSection(section);
        escapedSection.replace('\n', ' ');

        if(!_settings->contains(escapedSection))
            _settings->insert(escapedSection, new QHash<QString, QString>);
        _settings->value(escapedSection)->insert(escapedKey, value);
    }
}

QString PanoramaUI::sharedSetting(const QString &section, const QString &key)
{
    QString escapedKey(key);
    escapedKey.replace('\n', ' ');
    QString escapedSection(section);
    escapedSection.replace('\n', ' ');

    if(_settings && _settings->contains(escapedSection) && _settings->value(escapedSection)->contains(escapedKey))
        return _settings->value(escapedSection)->value(escapedKey);
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

QString PanoramaUI::loadFont(const QString &file, bool bold, bool italic)
{
    //TODO: support URLs!!
    QString path(qmlContext(this)->baseUrl().toLocalFile());
    path.resize(path.lastIndexOf("/") + 1);
    path.append(file);

    int font;
    if(_loadedFonts.contains(path))
        font = _loadedFonts[path];
    else
    {
        font = QFontDatabase::addApplicationFont(path);
        _loadedFonts[path] = font;
    }

    QStringList fonts = QFontDatabase::applicationFontFamilies(font);
    foreach(const QString &font, fonts)
    {
        /* bo cb it ci ok
         * 1  1  0  0  1
         * 0  0  1  1  1
         * 1  1  1  1  1
         * 0  0  0  0  1
         * *  *  *  *  0
         */
        if((bold == font.contains("bold", Qt::CaseInsensitive)) && (italic == font.contains("italic", Qt::CaseInsensitive)))
            return font;
    }
    if(fonts.count() > 0)
        return fonts[0];
    else
        return QString();
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
QHash<QString, int> PanoramaUI::_loadedFonts;
QHash<QString, QHash<QString, QString> *> *PanoramaUI::_settings = 0;

//Makes this type available in QML
QML_DEFINE_TYPE(Panorama,1,0,PanoramaUI,PanoramaUI);
