#ifndef MILKYMODEL_H
#define MILKYMODEL_H

#include "panoramainternal.h"
#include "milkylistener.h"
#include "milkydevice.h"
#include <QAbstractListModel>
#include <QtDeclarative>
#include <QStringList>

class MilkyModelPrivate;

class MilkyModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(QObject* categories   READ getCategories                  NOTIFY categoriesChanged)
    Q_PROPERTY(int     bytesDownloaded READ getBytesDownloaded)
    Q_PROPERTY(int     bytesToDownload READ getBytesToDownload)
    Q_PROPERTY(QString device        READ getDevice        WRITE setDevice        NOTIFY deviceChanged)
    Q_PROPERTY(QString targetDir     READ getTargetDir     WRITE setTargetDir     NOTIFY targetDirChanged)
    Q_PROPERTY(QString repositoryUrl READ getRepositoryUrl WRITE setRepositoryUrl NOTIFY repositoryUrlChanged)
    Q_PROPERTY(QString configFile    READ getConfigFile    WRITE setConfigFile    NOTIFY configFileChanged)
    Q_PROPERTY(QString logFile       READ getLogFile       WRITE setLogFile       NOTIFY logFileChanged)
    Q_PROPERTY(bool    hasUpgrades   READ getHasUpgrades   WRITE setHasUpgrades   NOTIFY hasUpgradesChanged)
    Q_PROPERTY(MilkyListener* events READ getListener                             NOTIFY listenerChanged)

    PANORAMA_DECLARE_PRIVATE(MilkyModel)
public:
    explicit MilkyModel(QObject *parent = 0);
    virtual ~MilkyModel();

    enum Roles
    {
        Id = Qt::UserRole,
        Title,
        Description,
        Info,
        Icon,
        Uri,
        MD5,
        Vendor,
        Group,
        Modified,
        Rating,
        Size,
        AuthorName,
        AuthorSite,
        AuthorEmail,
        InstalledVersionMajor,
        InstalledVersionMinor,
        InstalledVersionRelease,
        InstalledVersionBuild,
        InstalledVersionType,
        CurrentVersionMajor,
        CurrentVersionMinor,
        CurrentVersionRelease,
        CurrentVersionBuild,
        CurrentVersionType,
        Installed,
        HasUpdate,
        InstallPath,
        Categories,
        CategoriesString,
        PreviewPics,
        Licenses,
        SourceLinks
    };

    /** QML helper method that applies a filter to this model */
    Q_INVOKABLE QVariant inCategory(const QString &category);

    /** QML helper method that applies a filter to this model */
    Q_INVOKABLE QVariant matching(const QString &role, const QString &value);

    /** QML helper method that sorts this model */
    Q_INVOKABLE QVariant sortedBy(const QString &role, bool ascending);

    Q_INVOKABLE QVariant drop(int count);

    Q_INVOKABLE QVariant take(int count);


    /** Returns the number of items in this model */
    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    /** Returns the data at the specified index. */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    /** Returns the header for each role */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;

    QStringListModel* getCategories();

    int getBytesDownloaded() const;
    int getBytesToDownload() const;

    QString getDevice();
    void setDevice(QString const newDevice);
    Q_INVOKABLE QList<QObject*> getDeviceList();

    QString getTargetDir();
    void setTargetDir(QString const newTargetDir);
    Q_INVOKABLE QList<QObject*> getTargetPackages();

    QString getRepositoryUrl();
    void setRepositoryUrl(QString const newRepositoryUrl);

    QString getConfigFile();
    void setConfigFile(QString const newConfigFile);

    QString getLogFile();
    void setLogFile(QString const newLogFile);

    bool getHasUpgrades();
    void setHasUpgrades(bool const newLogFile);

    MilkyListener* getListener();

signals:
    void categoriesChanged(QStringListModel* categories);
    void deviceChanged(QString device);
    void targetDirChanged(QString targetDir);
    void repositoryUrlChanged(QString databaseFile);
    void configFileChanged(QString configFile);
    void logFileChanged(QString logFile);
    void listenerChanged(MilkyListener* listener);
    void hasUpgradesChanged(bool newHasUpgrades);

    void notifyListener();

public slots:
    void applyConfiguration();

    void updateDatabase();

    void addTarget(QString pndId);
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


private slots:
    void refreshModel();
    void finishInitialization();
};

QML_DECLARE_TYPE(MilkyModel)

#endif // MILKYMODEL_H
