#include "milkymodel.h"
#include "milky/milky.h"

#include <QDebug>
#include <QTimer>

class MilkyModelPrivate
{
    PANORAMA_DECLARE_PUBLIC(MilkyModel)
public:

};

MilkyModel::MilkyModel(QObject *parent) :
    QObject(parent)
{
    PANORAMA_INITIALIZE(MilkyModel);
    milky_init();
    milky_set_verbose(1);

    // Apply configuration after properties have been set
    QTimer* initTimer = new QTimer(this);
    initTimer->setInterval(0);
    initTimer->setSingleShot(true);
    connect(initTimer, SIGNAL(timeout()), this, SLOT(applyConfiguration()));
    initTimer->start();
}

MilkyModel::~MilkyModel()
{
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

QString MilkyModel::getDatabaseFile()
{
    return QString(milky_get_db());
}

void MilkyModel::setDatabaseFile(QString const newDatabaseFile)
{
    milky_set_db(newDatabaseFile.toLocal8Bit());
    emit databaseFileChanged(newDatabaseFile);
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

void MilkyModel::applyConfiguration()
{
    milky_check_config();
}
