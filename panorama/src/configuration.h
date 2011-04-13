#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QFileSystemWatcher>

#include "settingshive.h"

/**
 * Represents a configuration file for the Panorama application
 */
class Configuration : public QObject
{
Q_OBJECT
Q_PROPERTY(QString ui         READ ui         WRITE setUI)
Q_PROPERTY(QString uiDir      READ uiDir      WRITE setUIDir)
Q_PROPERTY(bool    fullscreen READ fullscreen WRITE setFullscreen)
public:
    /** Constructs a new Configuration instance */
    explicit Configuration(QObject *parent = 0);

    /** Sets the UI name field */
    void setUI(const QString &);

    /** Gets the UI name field */
    QString ui() const;

    /** Sets the UI search directory */
    void setUIDir(const QString &);

    /** Gets the UI search directory */
    QString uiDir() const;

    /** Sets start in fullscreen */
    void setFullscreen(const bool &);

    /** Gets start in fullscreen */
    bool fullscreen() const;

    /** Gets a pointer to the raw setting registry. */
    SettingsHive *generalConfig() const;

signals:
    /** The UI configuration has been changed */
    void uiChanged(const QString &uiDir, const QString &uiName);

public slots:
    /** Load the following file and replace the current values */
    void loadFile(const QString &file);

    /** Save the current configuration values to the current file */
    void saveFile();

private slots:
    void readFile(const QString &file);

    void reactToChange(const QString&, const QString&, const QString&,
                       SettingsHive::ChangeSource source);

private:
    QString _file;
    QString _ui;
    QString _uiDir;
    bool _fullscreen;
    QFileSystemWatcher _watcher;
    SettingsHive *_hive;
};

#endif // CONFIGURATION_H
