#include "milkylistener.h"

#include <QDebug>

class MilkyListenerPrivate
{
    PANORAMA_DECLARE_PUBLIC(MilkyListener)
public:
    bool listening;
};

MilkyListener::MilkyListener(QObject *parent) :
    QObject(parent)
{
    PANORAMA_INITIALIZE(MilkyListener);

    priv->listening = false;
    connect(this, SIGNAL(wait()), QThread::currentThread(), SLOT(sleepu));
}

MilkyListenerThread::MilkyListenerThread(QObject *parent) :
        QThread(parent), listener(0)
{
}

MilkyListenerThread::~MilkyListenerThread()
{
    if(listener)
        delete listener;
}

void MilkyListenerThread::run()
{
    listener = new MilkyListener();
    emit ready();
    exec();
}

void MilkyListenerThread::sleepu(unsigned long usecs = 10000)
{
    usleep(usecs);
}

void MilkyListener::answer(bool value)
{
    milky_answer(value ? 1 : 0);
}

void MilkyListener::listen()
{
    PANORAMA_PRIVATE(MilkyListener);

    if(priv->listening)
        return;

    priv->listening = true;

    _m_signal_t* signal;
    while((signal = milky_update()))
    {
        switch(signal->id)
        {
            case M_SIG_MESSAGE:
            {
                _m_sig_message* msgSignal = reinterpret_cast<_m_sig_message*>(signal);
                handleMessage(msgSignal);
                break;
            }
            case M_SIG_FETCH_START:
            {
                emit fetchStart();
                break;
            }
            case M_SIG_FETCH_DONE:
            {
                emit fetchDone();
                break;
            }
            case M_SIG_SYNC_START:
            {
                emit syncStart();
                break;
            }
            case M_SIG_SYNC_DONE:
            {
                emit syncDone();
                break;
            }
            case M_SIG_BACKUP_DATABASE:
            {
                emit creatingBackup();
                break;
            }
            case M_SIG_RESTORE_DATABASE:
            {
                emit restoringBackup();
                break;
            }
            case M_SIG_SAVE_START:
            {
                 emit saveStart();
                break;
            }
            case M_SIG_SAVE_DONE:
            {
                emit saveDone();
                break;
            }
            case M_SIG_UPGRADE_START:
            {
                emit upgradeStart();
                break;
            }
            case M_SIG_UPGRADE_DONE:
            {
                emit upgradeDone();
                break;
            }
            case M_SIG_UPGRADE_CHECK:
            {
                emit upgradeCheck();
                break;
            }
            case M_SIG_REMOVE_START:
            {
                emit removeStart();
                break;
            }
            case M_SIG_REMOVE_DONE:
            {
                emit removeDone();
                break;
            }
            case M_SIG_REMOVE_CHECK:
            {
                emit removeCheck();
                break;
            }
            case M_SIG_INSTALL_START:
            {
                emit installStart();
                break;
            }
            case M_SIG_INSTALL_DONE:
            {
                emit installDone();
                break;
            }
            case M_SIG_INSTALL_CHECK:
            {
                emit installCheck();
                break;
            }
            case M_SIG_CRAWL_START:
            {
                emit crawlStart();
                break;
            }
            case M_SIG_CRAWL_DONE:
            {
                emit crawlDone();
                break;
            }
            case M_SIG_CLEAN_START:
            {
                emit cleanStart();
                break;
            }
            case M_SIG_CLEAN_DONE:
            {
                emit cleanDone();
                break;
            }
            case M_SIG_DL_STARTED:
            {
                MilkyPackage package(static_cast<pnd_package*>(signal->data));
                emit downloadStarted(package.getId());
                break;
            }
            case M_SIG_DL_FINISHED:
            {
                MilkyPackage package(static_cast<pnd_package*>(signal->data));
                emit downloadFinished(package.getId());
                break;
            }
            case M_SIG_MD5_CHECK:
            {
                emit checkingMD5();
                break;
            }
            case M_SIG_PARSE_FILENAME:
            {
                emit parsingFilename();
                break;
            }
            case M_SIG_FILE_COPY:
            {
                emit copyingFile();
                break;
            }
            case M_SIG_WAIT: {
                break;
            }
            default:
            {
                emit wait();
                break;
            }
        }

        milky_free_signal(signal);
    }

    priv->listening = false;
}

void MilkyListener::handleMessage(_m_sig_message *msgSignal)
{
    switch(msgSignal->msg)
    {
        case M_MSG_PND_INSTALLING:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::Installing, package.getId());
            break;
        }
        case M_MSG_PND_REMOVING:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::Removing, package.getId());
            break;
        }
        case M_MSG_PND_UPGRADING:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::Upgrading, package.getId());
            break;
        }
        case M_MSG_CONFIG:
        {
            emit message(MilkyEvents::InvalidConfiguration, QVariant());
            break;
        }
        case M_MSG_DEVICE:
        {
            emit message(MilkyEvents::InvalidDevice, reinterpret_cast<char*>(msgSignal->data));
            break;
        }
        case M_MSG_DEVICE_MOUNT:
        {
            emit message(MilkyEvents::DeviceNotMounted, reinterpret_cast<char*>(msgSignal->data));
            break;
        }
        case M_MSG_JSON:
        {
            emit message(MilkyEvents::InvalidJSON, reinterpret_cast<char*>(msgSignal->data));
            break;
        }
        case M_MSG_HTTP_REQUEST:
        {
            emit message(MilkyEvents::HTTPError, reinterpret_cast<char*>(msgSignal->data));
            break;
        }
        case M_MSG_FILE_CREATE:
        {
            emit message(MilkyEvents::FileCreationError, QVariant());
            break;
        }
        case M_MSG_FILE_COPY_FAIL:
        {
            emit message(MilkyEvents::FileCopyError, QVariant());
            break;
        }
        case M_MSG_PND_NOT_FOUND:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::PNDNotFound, package.getId());
            break;
        }
        case M_MSG_PND_NOT_INSTALLED:
        {
            emit message(MilkyEvents::PNDNotInstalled, reinterpret_cast<char*>(msgSignal->data));
            break;
        }
        case M_MSG_PND_ALREADY_INSTALLED:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::PNDAlreadyInstalled, package.getId());
            break;
        }
        case M_MSG_PND_ALREADY_INSTALLED_SKIP:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::PNDSkippingAlreadyInstalled, package.getId());
            break;
        }
        case M_MSG_PND_REINSTALL:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::PNDReinstalling, package.getId());
            break;
        }
        case M_MSG_PND_ALREADY_UPDATE:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::PNDAlreadyUpdated, package.getId());
            break;
        }
        case M_MSG_PND_REMOVE_FAIL:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::PNDRemoveFailed, package.getId());
            break;
        }
        case M_MSG_PND_UPGRADE_FAIL:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::PNDUpgradeFailed, package.getId());
            break;
        }
        case M_MSG_PND_INSTALL_FAIL:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::PNDInstallFailed, package.getId());
            break;
        }
        case M_MSG_PND_HAS_UPDATE:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::PNDHasUpdate, package.getId());
            break;
        }
        case M_MSG_PND_REMOVED:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::PNDRemoved, package.getId());
            break;
        }
        case M_MSG_PND_FOUND:
        {
            MilkyPackage package(reinterpret_cast<pnd_package*>(msgSignal->data));
            emit message(MilkyEvents::PNDFound, package.getId());
            break;
        }
        case M_MSG_NO_TARGETS:
        {
            emit message(MilkyEvents::NoTargets, QVariant());
            break;
        }
        case M_MSG_NO_DATABASE:
        {
            emit message(MilkyEvents::NoDatabase, QVariant());
            break;
        }
        case M_MSG_NO_UPDATES:
        {
            emit message(MilkyEvents::NoUpdates, QVariant());
            break;
        }
        case M_MSG_MD5_FORCE:
        {
            emit message(MilkyEvents::MD5CheckFailedForce, QVariant());
            break;
        }
        case M_MSG_MD5_FAIL:
        {
            emit message(MilkyEvents::MD5CheckFailed, QVariant());
            break;
        }
        default:
        {
            break;
        }   
    }        
}
