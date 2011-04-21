#include "mainwindow.h"

#ifndef DISABLE_OPENGL
#include <QGLWidget>
#endif
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent)
{
    //"Clear" some memory
    _component = 0;
    _ui = 0;

    //Resize the window
    resize(UI_WIDTH, UI_HEIGHT);

    //Create our Canvas that we'll use later for the UI
    _canvas.setParent(this);
    _canvas.rootContext()->setContextProperty("ctxtHeight", UI_HEIGHT);
    _canvas.rootContext()->setContextProperty("ctxtWidth", UI_WIDTH);
    _canvas.setSource(QUrl("qrc:/root.qml"));
    _canvas.setFocusPolicy(Qt::StrongFocus);
    // TODO: _canvas.execute();
    this->setCentralWidget(&_canvas);

#ifndef DISABLE_OPENGL
    _canvas.setViewport(new QGLWidget());
#endif
    _canvas.setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
    _canvas.setOptimizationFlag(QGraphicsView::DontSavePainterState);

    _canvas.viewport()->setAttribute(Qt::WA_OpaquePaintEvent);
    _canvas.viewport()->setAttribute(Qt::WA_NoSystemBackground);
    _canvas.viewport()->setAttribute(Qt::WA_PaintUnclipped);
    _canvas.viewport()->setAttribute(Qt::WA_TranslucentBackground, false);

    _canvas.setStyleSheet("QGraphicsView { border-style: none; }");
    _canvas.setFrameStyle(0);
    _canvas.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    _canvas.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    _model.setParent(this);
    PanoramaUI::setApplicationsSource(&_model);

    //Set up the application loading/unloading procedure
    _accumulator.setParent(this);
    connect(&_accumulator, SIGNAL(appAdded(Application)),
            &_model, SLOT(addApp(Application)));
    connect(&_accumulator, SIGNAL(appRemoved(Application)),
            &_model, SLOT(removeApp(Application)));

    qRegisterMetaType<Application>("Application");

    //Load some actual applications from paths
    loadApps();

    //Set up UI loading and channel quit() events from QML
    connect(&_engine, SIGNAL(quit()), this, SLOT(close()));
    connect(this, SIGNAL(uiChanged(QString)), this, SLOT(loadUIFile(QString)));
    Setting::setSettingsSource(_config.generalConfig());

    _uiSetting = new Setting("panorama", "ui", QVariant(), this);
    _uiDirSetting = new Setting("panorama", "uiDirectory", QVariant(), this);
    _fullscreenSetting = new Setting("panorama", "fullscreen", QVariant(), this);

    connect(_uiSetting, SIGNAL(valueChanged(QVariant)), this, SLOT(changeUI()));
    connect(_uiDirSetting, SIGNAL(valueChanged(QVariant)), this, SLOT(changeUI()));
    connect(_fullscreenSetting, SIGNAL(valueChanged(QVariant)), this, SLOT(changeFullscreen()));

    _config.loadConfiguration();
}

void MainWindow::loadUIFile(const QString &file)
{
    //Clean up the old component
    if(_component)
        _component->deleteLater();

    //Create a generic component from the file
    _component = new QDeclarativeComponent(&_engine, file, this);

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
    QObject *obj(_component->create());

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
            _ui->setParentItem(qobject_cast<QDeclarativeItem*>(_canvas.rootObject()));
            connect(&_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
                    _ui, SLOT(propagateApplicationDataChange()));
            _ui->indicateLoadFinished();
            _ui->propagateApplicationDataChange();
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
        exit(0);
    }
    else if(e->key() == Qt::Key_F && e->modifiers() & Qt::ControlModifier)
    {
        if(isFullScreen())
        {
            showNormal();
        }
        else
        {
            showFullScreen();
        }
    }
}

void MainWindow::loadApps() {
    QStringList list;
    QStringList tmp;

    //XXX add whatever additional path that pndnotifyd spits .desktop files into
    tmp << QDir::root().filePath("usr") << "share" << "applications";
    list.append(tmp.join(QDir::separator()));

    tmp.clear();
    tmp << QDir::homePath() << ".local" << "share" << "applications";
    list.append(tmp.join(QDir::separator()));

    _accumulator.loadFrom(list);
}
