#include "applicationmodel.h"

#include "applicationfiltermethods.h"

class ApplicationModelPrivate
{
    PANORAMA_DECLARE_PUBLIC(ApplicationModel)
public:
    QList<Application> apps;
    QHash<int, QByteArray> roles;
};

ApplicationModel::ApplicationModel(QObject *parent) :
        QAbstractListModel(parent)
{
    PANORAMA_INITIALIZE(ApplicationModel);
    //"id" is a QML keyword, so we use "identifier" instead.
    priv->roles[ApplicationModel::Id]          = QString("identifier").toLocal8Bit();
    priv->roles[ApplicationModel::Name]        = QString("name")      .toLocal8Bit();
    priv->roles[ApplicationModel::Comment]     = QString("comment")   .toLocal8Bit();
    priv->roles[ApplicationModel::Icon]        = QString("icon")      .toLocal8Bit();
    priv->roles[ApplicationModel::Version]     = QString("version")   .toLocal8Bit();
    priv->roles[ApplicationModel::Categories]  = QString("categories").toLocal8Bit();

    setRoleNames(priv->roles);
}

ApplicationModel::~ApplicationModel()
{
    PANORAMA_UNINITIALIZE(ApplicationModel);
}

void ApplicationModel::addApp(const Application &app)
{
    PANORAMA_PRIVATE(ApplicationModel);
    //Store the app
    priv->apps += app;

    //Tell the View that it has to reload the end of the list
    const QModelIndex idx1 = createIndex(priv->apps.count() - 1, 0);
    const QModelIndex idx2 = createIndex(priv->apps.count(), 0);
    emit dataChanged(idx1, idx2);
}

void ApplicationModel::removeApp(const Application &app)
{
    PANORAMA_PRIVATE(ApplicationModel);
    for(int i = 0; i < priv->apps.count(); i++)
    {
        if(priv->apps.at(i).relatedFile == app.relatedFile)
        {
            //Remove the app
            priv->apps.removeAt(i);

            //Tell the View that it needs to reload part of the list
            const QModelIndex idx1 = createIndex(i - 1, 0);
            const QModelIndex idx2 = createIndex(i + 1, 0);
            emit dataChanged(idx1, idx2);
            break;
        }
    }
}

int ApplicationModel::rowCount(const QModelIndex &) const
{
    PANORAMA_PRIVATE(const ApplicationModel);
    return priv->apps.count();
}

QVariant ApplicationModel::data(const QModelIndex &index, int role) const
{
    PANORAMA_PRIVATE(const ApplicationModel);
    if(index.isValid() && index.row() < priv->apps.size())
    {
        const Application &value = priv->apps[index.row()];
        switch(role)
        {
        case ApplicationModel::Name:
            return value.name;
        case ApplicationModel::Comment:
            return value.comment;
        case ApplicationModel::Icon:
            return value.icon;
        case ApplicationModel::Version:
            return value.version;
        case ApplicationModel::Id:
            return value.id;
        case ApplicationModel::Categories:
            return value.categories;
        case ApplicationModel::Preview:
            return value.preview;
        case ApplicationModel::Clockspeed:
            return value.clockspeed;
        default:
            return QVariant();
        }
    }
    else
        return QVariant();
}

QVariant ApplicationModel::headerData(int, Qt::Orientation, int role) const
{
    switch(role)
    {
    case ApplicationModel::Name:
        return QString("Name");
    case ApplicationModel::Comment:
        return QString("Comment");
    case ApplicationModel::Icon:
        return QString("Icon path");
    case ApplicationModel::Version:
        return QString("Version");
    case ApplicationModel::Id:
        return QString("Command line");
    case ApplicationModel::Categories:
        return QString("FDF categories");
    case ApplicationModel::Preview:
        return QString("Preview image");
    case ApplicationModel::Clockspeed:
        return QString("Recommended clockspeed (MHz)");
    default:
        return QVariant();
    }
}


QVariant ApplicationModel::inCategory(const QString &category)
{
    return ApplicationFilterMethods::inCategory(this, category);
}

QVariant ApplicationModel::matching(const QString &role, const QString &value)
{
    return ApplicationFilterMethods::matching(this, role, value);
}

QVariant ApplicationModel::sortedBy(const QString &role, bool ascending)
{
    return ApplicationFilterMethods::sortedBy(this, role, ascending);
}

QVariant ApplicationModel::drop(int count)
{
    return ApplicationFilterMethods::drop(this, count);
}

QVariant ApplicationModel::take(int count)
{
    return ApplicationFilterMethods::take(this, count);
}
