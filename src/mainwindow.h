#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include <QtDeclarative/QmlEngine>
#include <QtDeclarative/QmlView>
#include <QtDeclarative/QmlComponent>
#include <QtDeclarative/QmlContext>
#include <QUrl>
#include <QFile>
#include <QtConcurrentRun>

#include "configuration.h"
#include "panoramaui.h"
#include "applicationmodel.h"
#include "appaccumulator.h"
#include "constants.h"
#include "setting.h"

/**
 * A MainWindow that is capable of displaying the Panorama's GUI
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /** Constructs a new MainWindow instance */
    MainWindow(QWidget *parent = 0);
    /** Destroys this MainWindow */
    ~MainWindow();

signals:
    /** A new UI file should be loaded */
    void uiChanged(const QString &uiFile);

public slots:
    /** Load the specified UI file */
    void loadUIFile(const QString &file);
    /** Change to the UI in the specified directory */
    void switchToUI(const QString &uiDir, const QString &uiName);

private slots:
    void continueLoadingUI();
    void useConfig(QHash<QString, QHash<QString, QString> *> *config);

private:
    void printError(const QmlComponent *obj) const;
    void loadApps();

    volatile bool appsLoaded;

    QmlEngine _engine;
    QmlView _canvas;
    QmlComponent *_component;
    PanoramaUI *_ui;
    Configuration _config;

    ApplicationModel _model;
    AppAccumulator _accumulator;
};

#endif // MAINWINDOW_H
