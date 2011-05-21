#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDeclarativeEngine>
#include <QDeclarativeView>
#include <QDeclarativeComponent>
#include <QDeclarativeContext>
#include <QUrl>
#include <QFile>
#include <QKeyEvent>

#include "constants.h"
#include "runtime.h"

/**
 * A MainWindow that is capable of displaying the Panorama's GUI
 */
class MainWindow : public QDeclarativeView
{
    Q_OBJECT

public:
    /** Constructs a new MainWindow instance */
    MainWindow(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent* e);
    void changeEvent(QEvent* e);

private:
    Runtime _runtimeObject;
};

#endif // MAINWINDOW_H
