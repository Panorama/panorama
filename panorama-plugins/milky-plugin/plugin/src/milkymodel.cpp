#include "milkymodel.h"
#include "milky/milky.h"

#include <QDebug>
#include <QTimer>
#include <QStringListModel>

#include "milkypackage.h"
#include "packagefiltermethods.h"

class MilkyModelPrivate
{
    PANORAMA_DECLARE_PUBLIC(MilkyModel)
public:
    MilkyListenerThread* listenerThread;
    QList<MilkyPackage*> packages;
    QStringListModel categories;
};

MilkyModel::MilkyModel(QObject *parent) :
    QAbstractListModel(parent)
{
    PANORAMA_INITIALIZE(MilkyModel);

    QHash<int, QByteArray> roles;
    roles[MilkyModel::Id] = QString("identifier").toLocal8Bit();
    roles[MilkyModel::Title] = QString("title").toLocal8Bit();
    roles[MilkyModel::Description] = QString("description").toLocal8Bit();
    roles[MilkyModel::Info] = QString("info").toLocal8Bit();
    roles[MilkyModel::Icon] = QString("icon").toLocal8Bit();
    roles[MilkyModel::Uri] = QString("uri").toLocal8Bit();
    roles[MilkyModel::MD5] = QString("md5").toLocal8Bit();
    roles[MilkyModel::Vendor] = QString("vendor").toLocal8Bit();
    roles[MilkyModel::Group] = QString("group").toLocal8Bit();
    roles[MilkyModel::Modified] = QString("modified").toLocal8Bit();
    roles[MilkyModel::Rating] = QString("rating").toLocal8Bit();
    roles[MilkyModel::Size] = QString("size").toLocal8Bit();
    roles[MilkyModel::AuthorName] = QString("authorName").toLocal8Bit();
    roles[MilkyModel::AuthorSite] = QString("authorSite").toLocal8Bit();
    roles[MilkyModel::AuthorEmail] = QString("authorEmail").toLocal8Bit();
    roles[MilkyModel::InstalledVersionMajor] = QString("installedVersionMajor").toLocal8Bit();
    roles[MilkyModel::InstalledVersionMinor] = QString("installedVersionMinor").toLocal8Bit();
    roles[MilkyModel::InstalledVersionRelease] = QString("installedVersionRelease").toLocal8Bit();
    roles[MilkyModel::InstalledVersionBuild] = QString("installedVersionBuild").toLocal8Bit();
    roles[MilkyModel::InstalledVersionType] = QString("installedVersionType").toLocal8Bit();
    roles[MilkyModel::CurrentVersionMajor] = QString("currentVersionMajor").toLocal8Bit();
    roles[MilkyModel::CurrentVersionMinor] = QString("currentVersionMinor").toLocal8Bit();
    roles[MilkyModel::CurrentVersionRelease] = QString("currentVersionRelease").toLocal8Bit();
    roles[MilkyModel::CurrentVersionBuild] = QString("currentVersionBuild").toLocal8Bit();
    roles[MilkyModel::CurrentVersionType] = QString("currentVersionType").toLocal8Bit();
    roles[MilkyModel::Installed] = QString("installed").toLocal8Bit();
    roles[MilkyModel::HasUpdate] = QString("hasUpdate").toLocal8Bit();
    roles[MilkyModel::InstallPath] = QString("installPath").toLocal8Bit();
    roles[MilkyModel::Categories] = QString("categories").toLocal8Bit();
    roles[MilkyModel::PreviewPics] = QString("previewPics").toLocal8Bit();
    setRoleNames(roles);

    milky_init();
    milky_set_verbose(3);

    priv->listenerThread = new MilkyListenerThread(this);
    connect(priv->listenerThread, SIGNAL(ready()), this, SLOT(finishInitialization()));
    priv->listenerThread->start();

    // Apply configuration after properties have been set
    QTimer* initTimer = new QTimer(this);
    initTimer->setInterval(0);
    initTimer->setSingleShot(true);
    connect(initTimer, SIGNAL(timeout()), this, SLOT(applyConfiguration()));
    initTimer->start();
}

MilkyModel::~MilkyModel()
{
    PANORAMA_PRIVATE(MilkyModel);
    priv->listenerThread->exit();

    milky_deinit();
}


QVariant MilkyModel::inCategory(const QString &category)
{
    return PackageFilterMethods::inCategory(this, category);
}

QVariant MilkyModel::matching(const QString &role, const QString &value)
{
    return PackageFilterMethods::matching(this, role, value);
}

QVariant MilkyModel::sortedBy(const QString &role, bool ascending)
{
    return PackageFilterMethods::sortedBy(this, role, ascending);
}

QVariant MilkyModel::drop(int count)
{
    return PackageFilterMethods::drop(this, count);
}

QVariant MilkyModel::take(int count)
{
    return PackageFilterMethods::take(this, count);
}

int MilkyModel::rowCount(const QModelIndex &) const
{
    PANORAMA_PRIVATE(const MilkyModel);
    return priv->packages.count();
}

QVariant MilkyModel::data(const QModelIndex &index, int role) const
{
    PANORAMA_PRIVATE(const MilkyModel);
    if(index.isValid() && index.row() < priv->packages.size())
    {
        const MilkyPackage* value = priv->packages.at(index.row());
        switch(role)
        {
        case Id:
            return value->getId();
        case Title:
            return value->getTitle();
        case Description:
            return value->getDescription();
        case Info:
            return value->getInfo();
        case Icon:
            return value->getIcon();
        case Uri:
            return value->getUri();
        case MD5:
            return value->getMD5();
        case Vendor:
            return value->getVendor();
        case Group:
            return value->getGroup();
        case Modified:
            return value->getModified();
        case Rating:
            return value->getRating();
        case Size:
            return value->getSize();
        case AuthorName:
            return value->getAuthorName();
        case AuthorSite:
            return value->getAuthorSite();
        case AuthorEmail:
            return value->getAuthorEmail();
        case InstalledVersionMajor:
            return value->getInstalledVersionMajor();
        case InstalledVersionMinor:
            return value->getInstalledVersionMinor();
        case InstalledVersionRelease:
            return value->getInstalledVersionRelease();
        case InstalledVersionBuild:
            return value->getInstalledVersionBuild();
        case InstalledVersionType:
            return value->getInstalledVersionType();
        case CurrentVersionMajor:
            return value->getCurrentVersionMajor();
        case CurrentVersionMinor:
            return value->getCurrentVersionMinor();
        case CurrentVersionRelease:
            return value->getCurrentVersionRelease();
        case CurrentVersionBuild:
            return value->getCurrentVersionBuild();
        case CurrentVersionType:
            return value->getCurrentVersionType();
        case Installed:
            return value->getInstalled();
        case HasUpdate:
            return value->getHasUpdate();
        case InstallPath:
            return value->getInstallPath();
        case Categories:
            return value->getCategories();
        case PreviewPics:
            return value->getPreviewPics();
        default:
            return QVariant();
        }
    }

    return QVariant();
}

QVariant MilkyModel::headerData(int, Qt::Orientation, int role) const
{
    switch(role)
    {
    case Id:
        return QString("Id");
    case Title:
        return QString("Title");
    case Description:
        return QString("Description");
    case Info:
        return QString("Info");
    case Icon:
        return QString("Icon");
    case Uri:
        return QString("Uri");
    case MD5:
        return QString("MD5");
    case Vendor:
        return QString("Vendor");
    case Group:
        return QString("Group");
    case Modified:
        return QString("Modified");
    case Rating:
        return QString("Rating");
    case Size:
        return QString("Size");
    case AuthorName:
        return QString("AuthorName");
    case AuthorSite:
        return QString("AuthorSite");
    case AuthorEmail:
        return QString("AuthorEmail");
    case InstalledVersionMajor:
        return QString("InstalledVersionMajor");
    case InstalledVersionMinor:
        return QString("InstalledVersionMinor");
    case InstalledVersionRelease:
        return QString("InstalledVersionRelease");
    case InstalledVersionBuild:
        return QString("InstalledVersionBuild");
    case InstalledVersionType:
        return QString("InstalledVersionType");
    case CurrentVersionMajor:
        return QString("CurrentVersionMajor");
    case CurrentVersionMinor:
        return QString("CurrentVersionMinor");
    case CurrentVersionRelease:
        return QString("CurrentVersionRelease");
    case CurrentVersionBuild:
        return QString("CurrentVersionBuild");
    case CurrentVersionType:
        return QString("CurrentVersionType");
    case Installed:
        return QString("Installed");
    case HasUpdate:
        return QString("HasUpdate");
    case InstallPath:
        return QString("InstallPath");
    case Categories:
        return QString("Categories");
    case PreviewPics:
        return QString("PreviewPics");
    default:
        return QVariant();
    }
}

QStringListModel* MilkyModel::getCategories() {
    PANORAMA_PRIVATE(MilkyModel);
    return &(priv->categories);
}

int MilkyModel::getBytesDownloaded() const
{
    __m_dl_status* status = milky_get_dl_status();
    return status ? status->now_downloaded : 0;
}

int MilkyModel::getBytesToDownload() const
{
    __m_dl_status* status = milky_get_dl_status();
    return status ? status->total_to_download : 0;
}

QString MilkyModel::getDevice()
{
    return QString(milky_get_dev());
}

void MilkyModel::setDevice(QString const newDevice)
{
    milky_set_dev(newDevice.toLocal8Bit());
    emit deviceChanged(newDevice);
}

QString MilkyModel::getTargetDir()
{
    return QString(milky_get_target_dir());
}

void MilkyModel::setTargetDir(QString const newTargetDir)
{
    milky_set_target_dir(newTargetDir.toLocal8Bit());
    emit targetDirChanged(newTargetDir);
}

QString MilkyModel::getRepositoryUrl()
{
    return QString(milky_get_db());
}

void MilkyModel::setRepositoryUrl(QString const newRepositoryUrl)
{
    milky_set_db(newRepositoryUrl.toLocal8Bit());
    emit repositoryUrlChanged(newRepositoryUrl);
}


QString MilkyModel::getConfigFile()
{
    return QString(milky_get_config_file());
}

void MilkyModel::setConfigFile(QString const newConfigFile)
{
    milky_set_config_file(newConfigFile.toLocal8Bit());
    emit configFileChanged(newConfigFile);
}


QString MilkyModel::getLogFile()
{
    return QString(milky_get_log_file());
}

void MilkyModel::setLogFile(QString const newLogFile)
{
    milky_set_log_file(newLogFile.toLocal8Bit());
    emit logFileChanged(newLogFile);
}

MilkyListener* MilkyModel::getListener()
{
    PANORAMA_PRIVATE(MilkyModel);
    return priv->listenerThread->listener;
}

void MilkyModel::applyConfiguration()
{
    milky_check_config();
    refreshModel();
}

void MilkyModel::updateDatabase()
{
    milky_sync_database();
    milky_crawl_pnd();
    emit notifyListener();
}

void MilkyModel::install(QString pndId)
{
    milky_add_target(pndId.toLocal8Bit());
    milky_check_config();
    milky_install();
    emit notifyListener();
}

void MilkyModel::remove(QString pndId)
{
    milky_add_target(pndId.toLocal8Bit());
    milky_check_config();
    milky_remove();
    emit notifyListener();
}

void MilkyModel::upgrade(QString pndId)
{
    milky_add_target(pndId.toLocal8Bit());
    milky_check_config();
    milky_upgrade();
    emit notifyListener();
}

void MilkyModel::answer(bool value)
{
    PANORAMA_PRIVATE(MilkyModel);
    priv->listenerThread->listener->answer(value);
}

void MilkyModel::refreshModel()
{
    PANORAMA_PRIVATE(MilkyModel);

    beginResetModel();

    milky_clear_targets();

    foreach(MilkyPackage* mp, priv->packages)
    {
        delete mp;
    }

    QStringList categoryList;

    priv->packages.clear();

    alpm_list_t* packageList = milky_get_package_list();
    alpm_list_t* package = packageList;

    if(package)
    {
        do
        {
            _pnd_package* p = reinterpret_cast<_pnd_package*>(package->data);
            MilkyPackage* mp = new MilkyPackage();

            mp->setId(p->id);
            mp->setTitle(p->title);
            mp->setDescription(p->desc);
            mp->setInfo(p->info);
            mp->setIcon(p->icon);
            mp->setUri(p->uri);
            mp->setMD5(p->md5);
            mp->setVendor(p->vendor);
            mp->setGroup(p->group);
            mp->setModified(QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(p->modified_time) * 1000));
            mp->setRating(p->rating);
            mp->setSize(p->size);
            mp->setAuthorName(p->author->name);
            mp->setAuthorSite(p->author->website);
            mp->setAuthorEmail(p->author->email);
            mp->setInstalledVersionMajor(p->local_version->major);
            mp->setInstalledVersionMinor(p->local_version->minor);
            mp->setInstalledVersionRelease(p->local_version->release);
            mp->setInstalledVersionBuild(p->local_version->build);
            mp->setInstalledVersionType(p->local_version->type);
            mp->setCurrentVersionMajor(p->version->major);
            mp->setCurrentVersionMinor(p->version->minor);
            mp->setCurrentVersionRelease(p->version->release);
            mp->setCurrentVersionBuild(p->version->build);
            mp->setCurrentVersionType(p->version->type);
            mp->setInstalled(p->installed);
            mp->setHasUpdate(p->hasupdate);
            mp->setInstallPath(p->install_path);

            QStringList packageCategories;
            alpm_list_t* categoryNode = p->categories;
            do
            {
                char* category = static_cast<char*>(categoryNode->data);
                packageCategories << category;
                if(!categoryList.contains(category))
                {
                    categoryList.append(category);
                }
            } while((categoryNode = categoryNode->next));


            alpm_list_t* previewPicNode = p->previewpics;
            if(previewPicNode)
            {
                QStringList previewPics;
                do
                {
                    char* previewPic = static_cast<char*>(previewPicNode->data);
                    previewPics << previewPic;
                } while((previewPicNode = previewPicNode->next));
                mp->setPreviewPics(previewPics);
            }

            priv->packages << mp;
        } while((package = package->next));
    }

    categoryList.sort();
    priv->categories.setStringList(categoryList);
    endResetModel();
}

void MilkyModel::finishInitialization()
{
    PANORAMA_PRIVATE(MilkyModel);
    connect(this, SIGNAL(notifyListener()), priv->listenerThread->listener, SLOT(listen()));
    connect(priv->listenerThread->listener, SIGNAL(crawlDone()), this, SLOT(refreshModel()));
    connect(priv->listenerThread->listener, SIGNAL(installDone()), this, SLOT(refreshModel()));
    connect(priv->listenerThread->listener, SIGNAL(removeDone()), this, SLOT(refreshModel()));
    connect(priv->listenerThread->listener, SIGNAL(upgradeDone()), this, SLOT(refreshModel()));
}
