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
};

MilkyModel::MilkyModel(QObject *parent) :
    QObject(parent)
{
    PANORAMA_INITIALIZE(MilkyModel);
    milky_init();
    milky_set_verbose(1);

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
}

void MilkyModel::updateDatabase()
{
    PANORAMA_PRIVATE(MilkyModel);
    milky_sync_database();
    emit notifyListener();
}

void MilkyModel::install(QString pndId)
{
    milky_add_target(pndId.toLocal8Bit());
    milky_install();
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

    foreach(MilkyPackage* mp, priv->packages)
    {
        delete mp;
    }
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
            mp->setmd5(p->md5);
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

            priv->packages << mp;
        } while(package = package->next);
    }
}

void MilkyModel::finishInitialization()
{
    PANORAMA_PRIVATE(MilkyModel);
    connect(this, SIGNAL(notifyListener()), priv->listenerThread->listener, SLOT(listen()));
    connect(priv->listenerThread->listener, SIGNAL(syncDone()), this, SLOT(refreshModel()));
}
