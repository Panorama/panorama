#ifndef MILKYMODEL_H
#define MILKYMODEL_H

#include "panoramainternal.h"
#include "milkylistener.h"

#include <QObject>
#include <QtDeclarative>

class MilkyModelPrivate;

class MilkyModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString device        READ getDevice        WRITE setDevice        NOTIFY deviceChanged)
    Q_PROPERTY(QString targetDir     READ getTargetDir     WRITE setTargetDir     NOTIFY targetDirChanged)
    Q_PROPERTY(QString repositoryUrl READ getRepositoryUrl WRITE setRepositoryUrl NOTIFY repositoryUrlChanged)
    Q_PROPERTY(QString configFile    READ getConfigFile    WRITE setConfigFile    NOTIFY configFileChanged)
    Q_PROPERTY(QString logFile       READ getLogFile       WRITE setLogFile       NOTIFY logFileChanged)
    Q_PROPERTY(MilkyListener* events       READ getListener                             NOTIFY listenerChanged)

    PANORAMA_DECLARE_PRIVATE(MilkyModel)
public:
    explicit MilkyModel(QObject *parent = 0);
    virtual ~MilkyModel();

    QString getDevice();
    void setDevice(QString const newDevice);

    QString getTargetDir();
    void setTargetDir(QString const newTargetDir);

    QString getRepositoryUrl();
    void setRepositoryUrl(QString const newRepositoryUrl);

    QString getConfigFile();
    void setConfigFile(QString const newConfigFile);

    QString getLogFile();
    void setLogFile(QString const newLogFile);

    MilkyListener* getListener();

signals:
    void deviceChanged(QString device);
    void targetDirChanged(QString targetDir);
    void repositoryUrlChanged(QString databaseFile);
    void configFileChanged(QString configFile);
    void logFileChanged(QString logFile);
    void listenerChanged(MilkyListener* listener);

    void notifyListener();

public slots:
    void applyConfiguration();

    void updateDatabase();
    void install(QString pndId);
    void answer(bool value);
};

QML_DECLARE_TYPE(MilkyModel)
#endif // MILKYMODEL_H
