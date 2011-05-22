#include "mainwindow.h"

#ifdef ENABLE_OPENGL
#include <QGLWidget>
#endif
#include <QCoreApplication>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
        QDeclarativeView(parent), _runtimeObject(this)
{
    //Set the runtime object context property
    rootContext()->setContextProperty("runtime", &_runtimeObject);
    connect(&_runtimeObject, SIGNAL(fullscreenRequested(bool)),
            this, SLOT(setFullscreen(bool)));

#ifdef ENABLE_OPENGL
    setViewport(new QGLWidget());
#endif
    viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    viewport()->setAttribute(Qt::WA_NoSystemBackground);
    viewport()->setAttribute(Qt::WA_PaintUnclipped);
    viewport()->setAttribute(Qt::WA_TranslucentBackground, false);

    setFocusPolicy(Qt::StrongFocus);
    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
    setOptimizationFlag(QGraphicsView::DontSavePainterState);
    setResizeMode(QDeclarativeView::SizeRootObjectToView);
    setStyleSheet("border-style: none;");
    setFrameStyle(0);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //Set up UI loading and channel quit() events from QML
    connect(engine(), SIGNAL(quit()), this, SLOT(close()));

    //Make plugins available
    engine()->addImportPath(QCoreApplication::applicationDirPath() + "/plugins");
    engine()->addImportPath("/usr/lib/panorama/plugins");
    engine()->addImportPath(QDir::homePath() + "/.panorama/plugins");

    //Load the main QML file
    setSource(QUrl("qrc:/root.qml"));

    //Resize to default size
    resize(UI_WIDTH, UI_HEIGHT);
}

void MainWindow::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::ActivationChange)
    {
        _runtimeObject.setIsActiveWindow(isActiveWindow());
    }
    QDeclarativeView::changeEvent(e);
}

void MainWindow::setFullscreen(bool fullscreen)
{
    if(fullscreen)
        setWindowState(windowState() | Qt::WindowFullScreen);
    else
        setWindowState(windowState() & ~Qt::WindowFullScreen);
}
