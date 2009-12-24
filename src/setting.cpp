#include "setting.h"

Setting::Setting(QObject *parent) :
    QObject(parent)
{
}

void Setting::setValue(const QString &value)
{
    if(_settings)
    {
        QString section(_section.isEmpty() ? _defaultSection : _section);
        section.replace('\n', ' ');
        QString key(_key);
        key.replace('\n', ' ');

        if(!_settings->contains(section))
            _settings->insert(section, new QHash<QString, QString>);
        _settings->value(section)->insert(key, value);
    }
}

QString Setting::value()
{
    QString section(_section.isEmpty() ? _defaultSection : _section);
    section.replace('\n', ' ');
    QString key(_key);
    key.replace('\n', ' ');

    if(_settings && _settings->contains(section) && _settings->value(section)->contains(key))
        return _settings->value(section)->value(key);
    else
        return QString();
}
