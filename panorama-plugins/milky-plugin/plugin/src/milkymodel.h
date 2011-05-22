#ifndef MILKYMODEL_H
#define MILKYMODEL_H

#include "panoramainternal.h"

#include <QObject>
#include <QtDeclarative>

class MilkyModelPrivate;

class MilkyModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString device       READ getDevice       WRITE setDevice       NOTIFY deviceChanged)
    Q_PROPERTY(QString targetDir    READ getTargetDir    WRITE setTargetDir    NOTIFY targetDirChanged)
    Q_PROPERTY(QString databaseFile READ getDatabaseFile WRITE setDatabaseFile NOTIFY databaseFileChanged)
    Q_PROPERTY(QString configFile   READ getConfigFile   WRITE setConfigFile   NOTIFY configFileChanged)
    Q_PROPERTY(QString logFile      READ getLogFile      WRITE setLogFile      NOTIFY logFileChanged)

    PANORAMA_DECLARE_PRIVATE(MilkyModel)
public:
    explicit MilkyModel(QObject *parent = 0);
    virtual ~MilkyModel();

    QString getDevice();
    void setDevice(QString const newDevice);

    QString getTargetDir();
    void setTargetDir(QString const newTargetDir);

    QString getDatabaseFile();
    void setDatabaseFile(QString const newDatabaseFile);

    QString getConfigFile();
    void setConfigFile(QString const newConfigFile);

    QString getLogFile();
    void setLogFile(QString const newLogFile);

signals:
    void deviceChanged(QString device);
    void targetDirChanged(QString targetDir);
    void databaseFileChanged(QString databaseFile);
    void configFileChanged(QString configFile);
    void logFileChanged(QString logFile);

public slots:
    void applyConfiguration();
};

QML_DECLARE_TYPE(MilkyModel)
#endif // MILKYMODEL_H
