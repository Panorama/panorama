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
    QList<QObject*> devices;
    QStringListModel categories;
    bool hasUpgrades;
};

MilkyModel::MilkyModel(QObject *parent) :
    QAbstractListModel(parent)
{
    PANORAMA_INITIALIZE(MilkyModel);

    priv->hasUpgrades = false;

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
    roles[MilkyModel::LastUpdatedString] = QString("lastUpdatedString").toLocal8Bit();
    roles[MilkyModel::Rating] = QString("rating").toLocal8Bit();
    roles[MilkyModel::Size] = QString("size").toLocal8Bit();
    roles[MilkyModel::SizeString] = QString("sizeString").toLocal8Bit();
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
    roles[MilkyModel::CategoriesString] = QString("categoriesString").toLocal8Bit();
    roles[MilkyModel::PreviewPics] = QString("previewPics").toLocal8Bit();
    roles[MilkyModel::Licenses] = QString("licenses").toLocal8Bit();
    roles[MilkyModel::SourceLinks] = QString("sourceLinks").toLocal8Bit();
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
        case LastUpdatedString:
            return value->getLastUpdatedString();
        case Rating:
            return value->getRating();
        case Size:
            return value->getSize();
        case SizeString:
            return value->getSizeString();
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
        case CategoriesString:
            return value->getCategoriesString();
        case PreviewPics:
            return value->getPreviewPics();
        case Licenses:
            return value->getLicenses();
        case SourceLinks:
            return value->getSourceLinks();
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
    case LastUpdatedString:
        return QString("LastUpdatedString");
    case Rating:
        return QString("Rating");
    case Size:
        return QString("Size");
    case SizeString:
        return QString("SizeString");
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
    case CategoriesString:
        return QString("CategoriesString");
    case PreviewPics:
        return QString("PreviewPics");
    case Licenses:
        return QString("Licenses");
    case SourceLinks:
        return QString("SourceLinks");
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
    _m_dl_status* status = milky_get_dl_status();
    return status ? status->now_downloaded : 0;
}

int MilkyModel::getBytesToDownload() const
{
    _m_dl_status* status = milky_get_dl_status();
    return status ? status->total_to_download : 0;
}

QString MilkyModel::getDevice()
{
    return QString(milky_get_dev());
}

void MilkyModel::setDevice(QString const newDevice)
{
    milky_set_dev(newDevice.toLocal8Bit());
    milky_check_config();
    emit deviceChanged(newDevice);
}

QList<QObject*> MilkyModel::getDeviceList()
{
    QList<QObject*> devices;

    alpm_list_t* deviceList = milky_list_devices();
    alpm_list_t* node = deviceList;
    while(node)
    {
        _m_dev_struct* device = static_cast<_m_dev_struct*>(node->data);
        devices.append(new MilkyDevice(device));
        node = node->next;
    }

    milky_free_device_list(deviceList);
    return devices;
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

QList<QObject*> MilkyModel::getTargetPackages()
{
    QList<QObject*> packages;

    alpm_list_t* node = milky_get_target_pnd();
    while(node)
    {
        _pnd_package* package = static_cast<_pnd_package*>(node->data);
        packages.append(new MilkyPackage(package));
        node = node->next;
    }

    return packages;
}

QList<QObject*> MilkyModel::getRepositories()
{
    QList<QObject*> repositories;

    alpm_list_t* node = milky_get_repositories();
    while(node)
    {
        pnd_repo* repo = static_cast<pnd_repo*>(node->data);
        repositories.append(new MilkyRepository(repo));
        node = node->next;
    }

    return repositories;
}

void MilkyModel::addRepository(QString url)
{
    milky_add_repository(url.toLocal8Bit());
}

void MilkyModel::removeRepository(QString url)
{
    milky_remove_repository(url.toLocal8Bit());
}

void MilkyModel::clearRepositories()
{
    milky_clear_repositories();
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

bool MilkyModel::getHasUpgrades()
{
    PANORAMA_PRIVATE(MilkyModel);
    return priv->hasUpgrades;
}

void MilkyModel::setHasUpgrades(bool const newHasUpgrades)
{
    PANORAMA_PRIVATE(MilkyModel);
    if(newHasUpgrades != priv->hasUpgrades)
    {
        priv->hasUpgrades = newHasUpgrades;
        emit hasUpgradesChanged(newHasUpgrades);
    }
}

bool MilkyModel::repositoryUpdated()
{
    return milky_get_changes_since(0) != 0;
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

void MilkyModel::crawlDevice()
{
    milky_check_config();
    milky_crawl_pnd();
    emit notifyListener();
}

void MilkyModel::syncWithRepository()
{
    milky_check_config();
    milky_sync_database();
    emit notifyListener();
}


void MilkyModel::addTarget(QString pndId)
{
    milky_add_target(pndId.toLocal8Bit());
}

void MilkyModel::removeTarget(QString pndId)
{
    milky_remove_target(pndId.toLocal8Bit());
}

void MilkyModel::clearTargets()
{
    milky_clear_targets();
}

void MilkyModel::install()
{
    milky_check_config();
    milky_install();
    emit notifyListener();
}

void MilkyModel::remove()
{
    milky_check_config();
    milky_remove();
    emit notifyListener();
}

void MilkyModel::upgrade()
{
    milky_check_config();
    milky_upgrade();
    emit notifyListener();
}

void MilkyModel::upgradeAll()
{
    PANORAMA_PRIVATE(MilkyModel);
    foreach(MilkyPackage* p, priv->packages)
    {
        if(p->getHasUpdate()) {
            addTarget(p->getId());
        }
    }

    upgrade();
}

void MilkyModel::install(QString pndId)
{
    clearTargets();
    addTarget(pndId);
    install();
}

void MilkyModel::remove(QString pndId)
{
    clearTargets();
    addTarget(pndId);
    remove();
}

void MilkyModel::upgrade(QString pndId)
{
    clearTargets();
    addTarget(pndId);
    upgrade();
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
    categoryList << ""; // "All" category

    priv->packages.clear();

    alpm_list_t* packageList = milky_get_package_list();
    alpm_list_t* package = packageList;

    setHasUpgrades(false);

    if(package)
    {
        do
        {
            _pnd_package* p = reinterpret_cast<_pnd_package*>(package->data);
            MilkyPackage* mp = new MilkyPackage(p);

            foreach(QString category, mp->getCategories())
            {
                if(!categoryList.contains(category))
                {
                    categoryList.append(category);
                }
            }

            if(mp->getHasUpdate())
            {
                setHasUpgrades(true);
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
    connect(priv->listenerThread->listener, SIGNAL(syncDone()), this, SLOT(refreshModel()));
    connect(priv->listenerThread->listener, SIGNAL(crawlDone()), this, SLOT(refreshModel()));
    connect(priv->listenerThread->listener, SIGNAL(installDone()), this, SLOT(refreshModel()));
    connect(priv->listenerThread->listener, SIGNAL(removeDone()), this, SLOT(refreshModel()));
    connect(priv->listenerThread->listener, SIGNAL(upgradeDone()), this, SLOT(refreshModel()));
}
