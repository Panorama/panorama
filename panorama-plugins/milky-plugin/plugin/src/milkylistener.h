#ifndef MILKYLISTENER_H
#define MILKYLISTENER_H

#include <QObject>
#include <QThread>
#include <QVariant>
#include <QMetaType>

#include "milky/milky.h"
#include "panoramainternal.h"

class MilkyListenerPrivate;

// Wrapper class to make the events available in QML
class MilkyEvents : public QObject
{
    Q_OBJECT
    Q_ENUMS(MessageType)

public:
    enum MessageType { InvalidConfiguration, InvalidDevice, DeviceNotMounted, InvalidJSON, HTTPError, FileCreationError,
                       FileCopyError, PNDNotFound, PNDNotInstalled, PNDAlreadyInstalled, PNDSkippingAlreadyInstalled,
                       PNDReinstalling, PNDAlreadyUpdated, PNDRemoveFailed, PNDUpgradeFailed, PNDInstallFailed,
                       PNDHasUpdate, PNDFound, NoTargets, NoDatabase, NoUpdates, MD5CheckFailed, MD5CheckFailedForce };
};

class MilkyListener : public QObject
{
    Q_OBJECT

    PANORAMA_DECLARE_PRIVATE(MilkyListener)

public:
    explicit MilkyListener(QObject *parent = 0);

signals:
    // Milky signals
    void message(QVariant type, QVariant data);
    void fetchStart();
    void fetchDone();
    void syncStart();
    void syncDone();
    void creatingBackup();
    void restoringBackup();
    void saveStart();
    void saveDone();
    void upgradeStart();
    void upgradeDone();
    void upgradeCheck();
    void removeStart();
    void removeDone();
    void removeCheck();
    void installStart();
    void installDone();
    void installCheck();
    void crawlStart();
    void crawlDone();
    void cleanStart();
    void cleanDone();
    void downloadFinished();
    void checkingMD5();
    void parsingFilename();
    void copyingFile();

public slots:
    void listen();
    void answer(bool value);

private:
    void handleMessage(__m_sig_message* msgSignal);
};

class MilkyListenerThread : public QThread
{
    Q_OBJECT
public:
    MilkyListenerThread(QObject* parent = 0);
    ~MilkyListenerThread();

    void run();
    MilkyListener* listener;

signals:
    void notifyListener();
};

#endif // MILKYLISTENER_H
