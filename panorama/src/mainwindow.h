#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QWidget>
#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QUrl>
#include <QFile>
#include <QKeyEvent>

#include "configuration.h"
#include "panoramaui.h"
#include "applicationmodel.h"
#include "appaccumulator.h"
#include "constants.h"
#include "setting.h"
#include "pandoraeventsource.h"

/**
 * A MainWindow that is capable of displaying the Panorama's GUI
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /** Constructs a new MainWindow instance */
    MainWindow(QWidget *parent = 0);

signals:
    /** A new UI file should be loaded */
    void uiChanged(const QString &uiFile);

public slots:
    /** Load the specified UI file */
    void loadUIFile(const QString &file);

    /** Change to the UI in the specified directory */
    void switchToUI(const QString &uiDir, const QString &uiName);

protected:
    void keyPressEvent(QKeyEvent* e);

private slots:
    void continueLoadingUI();
    void changeFullscreen();
    void changeUI();

private:
    void printError(const QDeclarativeComponent *obj) const;

    void loadApps();

    QDeclarativeView _canvas;
    QDeclarativeComponent *_component;
    PanoramaUI *_ui;

    Setting *_fullscreenSetting;
    Setting *_uiSetting;
    Setting *_uiDirSetting;
};

#endif // MAINWINDOW_H
