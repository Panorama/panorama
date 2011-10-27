#ifndef APPACCUMULATOR_H
#define APPACCUMULATOR_H

#include "panoramainternal.h"

#include <QObject>
#include <QString>
#include <QStringList>

#include "application.h"

class AppAccumulatorPrivate;

/**
 * Scans a set of search paths, finds all of the .desktop files in those search
 * paths and generates Application instances based on the found desktop files.
 *
 * It is not necessary to call "loadFrom" multiple times; INotify is used to
 * send out updated application instances automatically when a file changes.
 */
class AppAccumulator : public QObject
{
    Q_OBJECT
    PANORAMA_DECLARE_PRIVATE(AppAccumulator)
public:
    /** Constructs a new AppAccumulator instance */
    explicit AppAccumulator(QObject *parent = 0);
    ~AppAccumulator();

    /** Gets the application data structure for the given id */
    Application getApplication(const QString &id) const;

public slots:
    /** Loads all .desktop files from the specified search paths (not recursive) */
    void loadFrom(const QStringList &searchpaths, bool initial = true);

signals:
    /** An application has been found or added to one of the search paths */
    void appAdded(const Application &app, bool signalChange);

    /** An application has been removed from one of the search paths */
    void appRemoved(const Application &app);

    /** The initial set of applications have been loaded */
    void finishedInitialLoad();

protected slots:
    void rescanDir(const QString &dir);
};

#endif // APPACCUMULATOR_H
