#include "applicationattached.h"

#include "pnd_conf.h"
#include "pnd_apps.h"

#ifdef Q_OS_UNIX
extern "C"
{
#include <wordexp.h>
}
#endif

#include "appaccumulator.h"
#include "applicationmodel.h"
#include <QDir>
#include <QProcess>
#include <QDebug>

AppAccumulator *_applicationattached_accumulator = 0;
#define _accumulator _applicationattached_accumulator

ApplicationModel *_applicationattached_model = 0;
#define _model _applicationattached_model

ApplicationsAttached::ApplicationsAttached(QObject *parent) :
        QObject(parent)
{
    if(!_accumulator)
    {
        _accumulator = new AppAccumulator();
    }
    if(!_model)
    {
        _model = new ApplicationModel();
        connect(_accumulator, SIGNAL(appAdded(Application)),
                _model, SLOT(addApp(Application)));
        connect(_accumulator, SIGNAL(appRemoved(Application)),
                _model, SLOT(removeApp(Application)));
        //XXX Is this needed??
        connect(_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                this, SIGNAL(listChanged()));

        QStringList paths;

        QString configpath = pnd_conf_query_searchpath();
        pnd_conf_handle h = pnd_conf_fetch_by_id(pnd_conf_desktop, configpath.toUtf8().data());

        if(h)
        {
            QString desktopPath = pnd_conf_get_as_char(h, (char *)PND_DESKTOP_DOTDESKTOP_PATH_KEY);
            paths << desktopPath.split(QRegExp(":"), QString::SkipEmptyParts);

            QString menuPath = pnd_conf_get_as_char(h, (char *)PND_MENU_DOTDESKTOP_PATH_KEY);
            paths << menuPath.split(QRegExp(":"), QString::SkipEmptyParts);
        }
        else
            qWarning() << "Warning: No PND search path file found. "
                    "This means that applications in non-default places won't be found.";

        paths.append((QStringList() << QDir::root().filePath("usr") << "share" << "applications").join(QDir::separator()));
        paths.append((QStringList() << QDir::homePath() << ".local" << "share" << "applications").join(QDir::separator()));

#ifdef Q_OS_UNIX
        //Check whether some paths contain home directory references à la "~/foo/" or "~david/foo"
        QStringList absolutePaths;
        foreach(const QString &path, paths)
        {
            wordexp_t result;
            wordexp(path.toLocal8Bit(), &result, 0);
            absolutePaths << QDir(QString::fromLocal8Bit(result.we_wordv[0])).absolutePath();
        }

        _accumulator->loadFrom(absolutePaths);
#else
        _accumulator->loadFrom(paths);
#endif
    }
}

void ApplicationsAttached::execute(const QString &id) const
{
    Application app = _accumulator->getApplication(id);
    if(!app.exec.isEmpty())
    {
        QString command(app.exec);
        //Fill in FDF fields
        command.replace("%c", app.name);
        if(!app.icon.isEmpty())
            command.replace("%i", app.icon);
        command.replace("%k", app.relatedFile);
        command.remove(QRegExp("%\\w"));

        QProcess::startDetached(command);
    }
}

QVariant ApplicationsAttached::list() const
{
    return QVariant::fromValue((QObject *)_model);
}
