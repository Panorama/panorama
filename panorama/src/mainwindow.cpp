#include "mainwindow.h"

#ifdef ENABLE_OPENGL
#include <QGLWidget>
#endif
#include <QCoreApplication>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
        QDeclarativeView(parent), _component(0), _ui(0),
        _fullscreenSetting(0), _uiSetting(0), _uiDirSetting(0),
        runtimeObject(this)
{
    //Set the runtime object context property
    rootContext()->setContextProperty("runtime", &runtimeObject);

    //Create our Canvas that we'll use later for the UI
    setSource(QUrl("qrc:/root.qml"));
    setFocusPolicy(Qt::StrongFocus);
    if(!errors().isEmpty())
        qWarning() << errors();

#ifdef ENABLE_OPENGL
    setViewport(new QGLWidget());
#endif
    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
    setOptimizationFlag(QGraphicsView::DontSavePainterState);

    setResizeMode(QDeclarativeView::SizeRootObjectToView);
    resize(UI_WIDTH, UI_HEIGHT);

    viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    viewport()->setAttribute(Qt::WA_NoSystemBackground);
    viewport()->setAttribute(Qt::WA_PaintUnclipped);
    viewport()->setAttribute(Qt::WA_TranslucentBackground, false);

    setStyleSheet("border-style: none;");
    setFrameStyle(0);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    engine()->addImportPath(QCoreApplication::applicationDirPath() + "/plugins");

    //Set up UI loading and channel quit() events from QML
    connect(engine(), SIGNAL(quit()), this, SLOT(close()));
    connect(this, SIGNAL(uiChanged(QString)), this, SLOT(loadUIFile(QString)));

    _uiSetting = new Setting("panorama", "ui", QVariant(), this);
    _uiDirSetting = new Setting("panorama", "uiDirectory", QVariant(), this);
    _fullscreenSetting = new Setting("panorama", "fullscreen", QVariant(), this);

    connect(_uiSetting, SIGNAL(valueChanged(QVariant)), this, SLOT(changeUI()));
    connect(_uiDirSetting, SIGNAL(valueChanged(QVariant)), this, SLOT(changeUI()));
    connect(_fullscreenSetting, SIGNAL(valueChanged(QVariant)), this, SLOT(changeFullscreen()));
    changeFullscreen();
    changeUI();
}

void MainWindow::loadUIFile(const QString &file)
{
    //Clean up the old component
    if(_component)
        _component->deleteLater();

    //Create a generic component from the file
    _component = new QDeclarativeComponent(engine(), file, this);

    //Check if the component has errors and print them
    printError(_component);

    //Try to load the component immediately, or delay the load until when it
    //has finished loading
    if(_component->isReady() && !_component->isError())
        continueLoadingUI();
    else if(!_component->isError())
        connect(_component, SIGNAL(statusChanged(QDeclarativeComponent::Status)),
                this, SLOT(continueLoadingUI()));
}

void MainWindow::printError(const QDeclarativeComponent *c) const
{
    if(c->isError())
    {
        QList<QDeclarativeError> errorList = c->errors();
        foreach (const QDeclarativeError &error, errorList)
            qWarning() << error;
        return;
    }
}

void MainWindow::continueLoadingUI()
{
    //If this is a delayed load, remove the old connection
    disconnect(_component, SIGNAL(statusChanged(QDeclarativeComponent::Status)),
               this, SLOT(continueLoadingUI()));

    //Cehck errors again (now that the component is loaded)
    printError(_component);

    //Create an instance of the component
    QObject *obj(_component->create(rootContext()));

    //Check errors again (now that the component is created)
    printError(_component);

    if(!_component->isError())
    {
        //Remove the old UI
        if(_ui)
            _ui->deleteLater();

        //Try to load the new component instance as our new UI
        _ui = qobject_cast<PanoramaUI *>(obj);

        //By now, we should have an UI unless the UI designer was stupid and
        //didn't put a Panorama UI in the file at all
        if(_ui)
        {
            _ui->setParentItem(qobject_cast<QDeclarativeItem*>(rootObject()));
            _ui->indicateLoadFinished();
        }
        else
            qWarning() << "The specified UI file does not contain "
                    "a Panorama UI";
    }
}


void MainWindow::changeFullscreen()
{
    if(_fullscreenSetting->value().toBool())
        showFullScreen();
    else
        showNormal();
}

void MainWindow::changeUI()
{
    if(!_uiDirSetting->value().toString().isEmpty())
        switchToUI(_uiDirSetting->value().toString(), _uiSetting->value().toString());
}

void MainWindow::switchToUI(const QString &uiDir, const QString &uiName)
{
    QString newUiDir;
    if(!QFileInfo(uiDir).exists() || //Dir cannot be found
       (!uiDir.contains(":") && //Dir is not an URL
       QDir(uiDir).isRelative())) { //Dir is potentially relative
        QDir dir = QDir(QCoreApplication::applicationDirPath());
        dir.cd(uiDir);
        newUiDir = dir.absolutePath();
    } else
        newUiDir = uiDir;
    emit uiChanged(QString(newUiDir).append(QDir::separator()).append(uiName)
                   .append(QDir::separator()).append("ui.qml"));
}

void MainWindow::keyPressEvent(QKeyEvent* e)
{
    if(e->key() == Qt::Key_Q && e->modifiers() & Qt::ControlModifier)
    {
        close();
        e->accept();
    }
    else if(e->key() == Qt::Key_F && e->modifiers() & Qt::ControlModifier)
    {
        _fullscreenSetting->setValue(!_fullscreenSetting->value().toBool());
        e->accept();
    }
    else
    {
        QDeclarativeView::keyPressEvent(e);
    }
}

void MainWindow::changeEvent(QEvent *e)
{
    if(e->type() == QEvent::ActivationChange)
    {
        runtimeObject.setIsActiveWindow(isActiveWindow());
    }
    QDeclarativeView::changeEvent(e);
}
