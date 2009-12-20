#include "configuration.h"

Configuration::Configuration(QObject *parent) :
    QObject(parent)
{
    _generalConfig = 0;
}

void Configuration::loadFile(const QString &f)
{
    if(_watcher.files().contains(_file))
        _watcher.removePath(_file);

    _file = f;

    //Try to read the file once
    readFile(f);

    //Only add the file to the watcher if it exists
    if(!_watcher.files().contains(f) && QFileInfo(f).exists())
        _watcher.addPath(f);

    connect(&_watcher, SIGNAL(fileChanged(QString)), this, SLOT(readFile(QString)));
}

void Configuration::readFile(const QString &f)
{
    QString line;
    QString section;
    QHash<QString, QHash<QString, QString> *> *newConfig = new QHash<QString, QHash<QString, QString> *>;
    QFile file(f);
    bool changed(false);

    //For some reason, the FileWatcher stops tracking files sometimes...
    //(Probably when editors delete+recreate a file instead of modifying it)
    //Thus, we might have to readd it
    if(!_watcher.files().contains(f) && QFileInfo(f).exists())
        _watcher.addPath(f);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qWarning() << "Could not open file " << f;
        return;
    }

    QTextStream in(&file);

    while(!in.atEnd())
    {
        //XXX Optimize this
        line = in.readLine().trimmed();
        if(line.startsWith("#"))
            continue;
        else if(line.startsWith("["))
            section = line.mid(1, line.length() - 2);
        else if(section.isEmpty() && line.startsWith("uiDirectory"))
        {
            QStringList parts = line.split("=");
            if(parts.count() > 1)
            {
                parts.removeFirst();
                line = parts.join("=").trimmed();

                if(line.startsWith("\""))
                    line = line.mid(1, line.length() - 2);

                if(_uiDir != line)
                {
                    _uiDir = line;
                    changed = true;
                }
            }
        }
        else if(section.isEmpty() && line.startsWith("ui"))
        {
            QStringList parts = line.split("=");
            if(parts.count() > 1)
            {
                parts.removeFirst();
                line = parts.join("=").trimmed();

                if(line.startsWith("\""))
                    line = line.mid(1, line.length() - 2);

                if(_ui != line)
                {
                    _ui = line;
                    changed = true;
                }
            }
        }
        else
        {
            QStringList parts = line.split("=");
            if(parts.length() > 1)
            {
                if(!newConfig->contains(section))
                    newConfig->insert(section, new QHash<QString, QString>);

                const QString key = parts[0].trimmed();
                parts.removeFirst();
                QString value = parts.join("=").trimmed();

                if(value.startsWith('"'))
                    value = value.mid(1, value.length() - 2);

                newConfig->value(section)->insert(key, value);
            }
        }
    }
    file.close();

    if(!_generalConfig) //We do NOT want to overwrite the config at runtime!
    {
        _generalConfig = newConfig;
        emit generalConfigChanged(_generalConfig);
    }
    else
        delete newConfig;

    if(changed)
        emit uiChanged(_uiDir, _ui);
}

void Configuration::saveFile(const QString &f)
{
    QFile file(f);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qWarning() << "Could not open file " << _file;
        return;
    }

    QTextStream out(&file);

    out << "uiDirectory = \"" << _uiDir << '\"' << endl;
    out << "ui = \"" << _ui << '\"' << endl;

    foreach(const QString &section, _generalConfig->keys())
    {
        out << endl << "[" << section << "]" << endl;
        foreach(const QString &key, _generalConfig->value(section)->keys())
        {
            out << key << " = \""
                    << QString(_generalConfig->value(section)->value(key)).replace('\n', ' ')
                    << '\"' << endl;
        }
    }

    file.flush();
    file.close();
}

QString Configuration::ui() const
{
    return _ui;
}

QString Configuration::uiDir() const
{
    return _uiDir;
}

QHash<QString, QHash<QString, QString> *> *Configuration::generalConfig() const
{
    return _generalConfig;
}

void Configuration::setUI(const QString &value)
{
    if(_ui != value)
    {
        _ui = value;
        emit uiChanged(_uiDir, _ui);
    }
}

void Configuration::setUIDir(const QString &value)
{
    _uiDir = value;
}

Configuration::~Configuration()
{
    if(_generalConfig)
    {
        foreach(const QString &key, _generalConfig->keys())
            delete _generalConfig->value(key);
        delete _generalConfig;
    }
}
