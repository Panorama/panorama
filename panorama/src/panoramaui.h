#ifndef PANORAMASKIN_H
#define PANORAMASKIN_H

#include "panoramainternal.h"

#include <QObject>
#include <QString>
#include <QProcess>
#include <QAbstractItemModel>
#include <QDeclarativeItem>

#include "appaccumulator.h"
#include "constants.h"
#include "setting.h"

class PanoramaUIPrivate;

/**
 * The base class for all PanoramaUI instances.
 * This class is extended from actual .qml files via the QtScript core
 */
class PanoramaUI : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(QString name        READ name        WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(QString author      READ author      WRITE setAuthor)
    PANORAMA_DECLARE_PRIVATE(PanoramaUI)
public:
    /** Constructs a new PanoramaUI instance */
    explicit PanoramaUI(QDeclarativeItem *parent = 0);
    ~PanoramaUI();

    /** Gets the name */
    QString name() const;

    /** Sets the name */
    void setName(const QString&);

    /** Gets the description */
    QString description() const;

    /** Sets the description */
    void setDescription(const QString&);

    /** Gets the author */
    QString author() const;

    /** Sets the author */
    void setAuthor(const QString&);

public slots:
    /** Called when this instance has been loaded */
    void indicateLoadFinished();

signals:
    /** This UI has finished loading */
    void loaded();
};

//Makes this type available in QML
QML_DECLARE_TYPE(PanoramaUI);

#endif // PANORAMASKIN_H
