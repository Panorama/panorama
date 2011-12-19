#include "milkymodel.h"
#include "milky/milky.h"

#include <QDebug>
#include <QTimer>

#include "milkypackage.h"

class MilkyModelPrivate
{
    PANORAMA_DECLARE_PUBLIC(MilkyModel)
public:
    MilkyListenerThread* listenerThread;
    QList<MilkyPackage*> packages;
    QList<QObject*> devices;
    QList<MilkyPackage*> targets;
    QStringListModel categories;
    bool hasUpgrades;
};

MilkyModel::MilkyModel(QObject *parent) :
    MilkyPackageList(parent)
{
    PANORAMA_INITIALIZE(MilkyModel);

    priv->hasUpgrades = false;

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
    milky_cancel_all();
    priv->listenerThread->quit();
    priv->listenerThread->wait();
    milky_deinit();
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
    PANORAMA_PRIVATE(MilkyModel);
    QList<QObject*> targetPackages;

    foreach(MilkyPackage* package, priv->targets)
    {
        targetPackages.append(new MilkyPackage(*package));
    }

    return targetPackages;
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


MilkyPackage* MilkyModel::getPackage(QString pndId)
{
    for(int i = 0; i < packages.length(); ++i)
    {
        if(packages.at(i)->getId() == pndId)
        {
            return new MilkyPackage(*packages.at(i).data());
        }
    }

    return 0;
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
    PANORAMA_PRIVATE(MilkyModel);
    priv->targets.append(getPackage(pndId));
}

void MilkyModel::addUpgradableTargets()
{
    foreach(QSharedPointer<MilkyPackage> p, packages)
    {
        if(p->getHasUpdate()) {
            addTarget(p->getId());
        }
    }
}

void MilkyModel::removeTarget(QString pndId)
{
    PANORAMA_PRIVATE(MilkyModel);
    for(QList<MilkyPackage*>::iterator i = priv->targets.begin(); i != priv->targets.end(); ++i) {
        if((*i)->getId() == pndId) {
            i = priv->targets.erase(i);
        }
    }
}

void MilkyModel::clearTargets()
{
    PANORAMA_PRIVATE(MilkyModel);
    priv->targets.clear();
}

void MilkyModel::install()
{
    PANORAMA_PRIVATE(MilkyModel);

    foreach(MilkyPackage* package, priv->targets)
    {
        milky_add_target_id(package->getId().toLocal8Bit());

        milky_check_targets();
        milky_check_config();
        int jobId = milky_install();
        emit notifyListener();
        emit installQueued(package, jobId);
        milky_clear_targets();
        milky_check_targets();
    }

    clearTargets();
}

void MilkyModel::remove()
{
    PANORAMA_PRIVATE(MilkyModel);

    foreach(MilkyPackage* package, priv->targets)
    {
        milky_add_target_id(package->getId().toLocal8Bit());
        milky_check_targets();
        milky_check_config();

        int jobId = milky_remove();
        emit notifyListener();

        milky_clear_targets();
        milky_check_targets();
    }

    clearTargets();
}

void MilkyModel::upgrade()
{
    PANORAMA_PRIVATE(MilkyModel);

    foreach(MilkyPackage* package, priv->targets)
    {
        milky_add_target_id(package->getId().toLocal8Bit());
        milky_check_targets();
        milky_check_config();

        int jobId = milky_upgrade();
        emit notifyListener();
        emit upgradeQueued(package, jobId);

        milky_clear_targets();
        milky_check_targets();
    }

    clearTargets();
}

void MilkyModel::upgradeAll()
{
    addUpgradableTargets();
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

void MilkyModel::cancelJob(int jobId)
{
    milky_cancel(jobId);
    emit notifyListener();
}

void MilkyModel::refreshModel()
{
    PANORAMA_PRIVATE(MilkyModel);

    beginResetModel();

    milky_clear_targets();
    milky_check_targets();

    QStringList categoryList;
    categoryList << ""; // "All" category

    clear();

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

            addPackage(mp);
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
