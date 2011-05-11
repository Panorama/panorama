#include "applicationattached.h"

#include "appaccumulator.h"
#include "applicationmodel.h"
#include <QDir>
#include <QProcess>

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

        QStringList list;
        QStringList tmp;

        //XXX add whatever additional path that pndnotifyd spits .desktop files into
        tmp << QDir::root().filePath("usr") << "share" << "applications";
        list.append(tmp.join(QDir::separator()));

        tmp.clear();
        tmp << QDir::homePath() << ".local" << "share" << "applications";
        list.append(tmp.join(QDir::separator()));

        _accumulator->loadFrom(list);
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
