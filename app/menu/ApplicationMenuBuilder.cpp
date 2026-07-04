#include "ApplicationMenuBuilder.h"
#include "../../runtime/bootstrap/WindowId.h"
#include <QMenu>
#include <QAction>
#include <QCoreApplication>

ApplicationMenuBuilder::ApplicationMenuBuilder() {}
ApplicationMenuBuilder::~ApplicationMenuBuilder() {}

void ApplicationMenuBuilder::build(std::shared_ptr<IEventBus> eventBus) {
    QMenuBar *menuBar = new QMenuBar(nullptr);

    QMenu *appMenu = menuBar->addMenu("SWM Desk");
    
    QAction *aboutAction = appMenu->addAction("About SWM Desk");
    QObject::connect(aboutAction, &QAction::triggered, [eventBus]() {
        eventBus->publish(RuntimeEvent::WindowRequest, WindowCommand{WindowId::About, WindowAction::Show});
    });

    QAction *prefsAction = appMenu->addAction("Preferences...");
    prefsAction->setShortcut(QKeySequence("Ctrl+,"));
    QObject::connect(prefsAction, &QAction::triggered, [eventBus]() {
        eventBus->publish(RuntimeEvent::WindowRequest, WindowCommand{WindowId::Settings, WindowAction::Show});
    });

    appMenu->addSeparator();
    appMenu->addAction("Services");
    appMenu->addSeparator();
    appMenu->addAction("Hide SWM Desk");
    appMenu->addAction("Hide Others");
    appMenu->addAction("Show All");
    appMenu->addSeparator();

    QAction *quitAction = appMenu->addAction("Quit SWM Desk");
    quitAction->setShortcut(QKeySequence("Ctrl+Q"));
    QObject::connect(quitAction, &QAction::triggered, []() {
        QCoreApplication::quit();
    });

    QMenu *fileMenu = menuBar->addMenu("File");
    fileMenu->addAction("New Project");
    fileMenu->addAction("Open...");
    fileMenu->addAction("Open Recent");
    fileMenu->addSeparator();
    fileMenu->addAction("Close Window");

    QMenu *editMenu = menuBar->addMenu("Edit");
    editMenu->addAction("Undo");
    editMenu->addAction("Redo");
    editMenu->addSeparator();
    editMenu->addAction("Cut");
    editMenu->addAction("Copy");
    editMenu->addAction("Paste");
    editMenu->addAction("Delete");
    editMenu->addAction("Select All");

    QMenu *viewMenu = menuBar->addMenu("View");
    viewMenu->addAction("Dashboard");
    viewMenu->addAction("Studio");
    viewMenu->addAction("Library");
    viewMenu->addAction("Store");
    viewMenu->addSeparator();

    QAction *logViewerAction = viewMenu->addAction("Open Log Viewer");
    logViewerAction->setShortcut(QKeySequence("Ctrl+Shift+L"));
    QObject::connect(logViewerAction, &QAction::triggered, [eventBus]() {
        eventBus->publish(RuntimeEvent::WindowRequest, WindowCommand{WindowId::LogViewer, WindowAction::Show});
    });

    QAction *reloadUiAction = viewMenu->addAction("Reload UI");
    QObject::connect(reloadUiAction, &QAction::triggered, [eventBus]() {
        eventBus->publish(RuntimeEvent::ReloadUI, std::any());
    });

    viewMenu->addAction("Toggle Full Screen");

    QMenu *historyMenu = menuBar->addMenu("History");
    historyMenu->addAction("Recent Projects");
    historyMenu->addAction("Recent Logs");

    QMenu *windowMenu = menuBar->addMenu("Window");
    windowMenu->addAction("Minimize");
    windowMenu->addAction("Zoom");
    windowMenu->addSeparator();
    
    QAction *graphicsPreviewAction = windowMenu->addAction("Graphics Preview");
    graphicsPreviewAction->setShortcut(QKeySequence("Ctrl+Shift+G"));
    QObject::connect(graphicsPreviewAction, &QAction::triggered, [eventBus]() {
        eventBus->publish(RuntimeEvent::WindowRequest, WindowCommand{WindowId::GraphicsPreview, WindowAction::Show});
    });

    windowMenu->addSeparator();
    windowMenu->addAction("Bring All To Front");

    QMenu *helpMenu = menuBar->addMenu("Help");
    helpMenu->addAction("SWM Documentation");
    helpMenu->addAction("Keyboard Shortcuts");
    helpMenu->addAction("Report Issue");
    helpMenu->addAction("About Runtime");
}
