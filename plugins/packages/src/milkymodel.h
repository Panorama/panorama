#ifndef MILKYMODEL_H
#define MILKYMODEL_H

#include "panoramainternal.h"
#include "milkylistener.h"
#include "milkydevice.h"
#include "milkyrepository.h"
#include "milkypackagelist.h"
#include <QAbstractListModel>
#include <QtDeclarative>
#include <QStringList>

class MilkyModelPrivate;

class MilkyModel : public MilkyPackageList
{
    Q_OBJECT
    Q_PROPERTY(QObject* categories   READ getCategories                  NOTIFY categoriesChanged)
    Q_PROPERTY(int     bytesDownloaded READ getBytesDownloaded)
    Q_PROPERTY(int     bytesToDownload READ getBytesToDownload)
    Q_PROPERTY(QString device        READ getDevice        WRITE setDevice        NOTIFY deviceChanged)
    Q_PROPERTY(QString targetDir     READ getTargetDir     WRITE setTargetDir     NOTIFY targetDirChanged)
    Q_PROPERTY(QList<QObject*> repositories READ getRepositories NOTIFY repositoriesChanged)
    Q_PROPERTY(QString configFile    READ getConfigFile    WRITE setConfigFile    NOTIFY configFileChanged)
    Q_PROPERTY(QString logFile       READ getLogFile       WRITE setLogFile       NOTIFY logFileChanged)
    Q_PROPERTY(bool    hasUpgrades   READ getHasUpgrades   WRITE setHasUpgrades   NOTIFY hasUpgradesChanged)
    Q_PROPERTY(MilkyListener* events READ getListener                             NOTIFY listenerChanged)

    PANORAMA_DECLARE_PRIVATE(MilkyModel)
public:
    explicit MilkyModel(QObject *parent = 0);
    virtual ~MilkyModel();

    QStringListModel* getCategories();

    int getBytesDownloaded() const;
    int getBytesToDownload() const;

    QString getDevice();
    void setDevice(QString const newDevice);
    Q_INVOKABLE QList<QObject*> getDeviceList();

    QString getTargetDir();
    void setTargetDir(QString const newTargetDir);
    Q_INVOKABLE QList<QObject*> getTargetPackages();

    QList<QObject*> getRepositories();
    Q_INVOKABLE void addRepository(QString url);
    Q_INVOKABLE void removeRepository(QString url);
    Q_INVOKABLE void clearRepositories();

    Q_INVOKABLE MilkyPackage* getPackage(QString pndId);

    QString getConfigFile();
    void setConfigFile(QString const newConfigFile);

    QString getLogFile();
    void setLogFile(QString const newLogFile);

    bool getHasUpgrades();
    void setHasUpgrades(bool const newHasUpgrades);

    Q_INVOKABLE bool repositoryUpdated();

    MilkyListener* getListener();

signals:
    void categoriesChanged(QStringListModel* categories);
    void deviceChanged(QString device);
    void targetDirChanged(QString targetDir);
    void repositoriesChanged(QList<MilkyRepository*> repositories);
    void configFileChanged(QString configFile);
    void logFileChanged(QString logFile);
    void listenerChanged(MilkyListener* listener);
    void hasUpgradesChanged(bool newHasUpgrades);

    void notifyListener();

    void installQueued(QObject* pnd, int jobId);
    void upgradeQueued(QObject* pnd, int jobId);

public slots:
    void applyConfiguration();

    void crawlDevice();
    void syncWithRepository();

    void addTarget(QString pndId);
    void addUpgradableTargets();
    void removeTarget(QString pndId);
    void clearTargets();

    void install();
    void remove();
    void upgrade();
    void upgradeAll();

    void install(QString pndId);
    void remove(QString pndId);
    void upgrade(QString pndId);
    void answer(bool value);

    void cancelJob(int jobId);


private slots:
    void refreshModel();
    void finishInitialization();
};

QML_DECLARE_TYPE(MilkyModel)

#endif // MILKYMODEL_H
