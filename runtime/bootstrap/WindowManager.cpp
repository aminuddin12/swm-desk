#include "WindowManager.h"
#include "WindowFactory.h"
#include <QCoreApplication>
#include <QMetaObject>

WindowManager::WindowManager(std::shared_ptr<IEventBus> eventBus, QObject *parent)
    : QObject(parent), bus(eventBus) {
}

WindowManager::~WindowManager() {
    shutdown();
}

void WindowManager::initialize() {
}

void WindowManager::start() {
    if (bus) {
        tokenRequest = bus->subscribe(RuntimeEvent::WindowRequest, [this](const std::any &payload) {
            auto cmd = std::any_cast<WindowCommand>(payload);
            QMetaObject::invokeMethod(this, [this, cmd]() {
                switch (cmd.action) {
                    case WindowAction::Show:
                        showWindow(cmd.id);
                        break;
                    case WindowAction::Hide:
                        closeWindow(cmd.id);
                        break;
                    case WindowAction::Toggle:
                        toggleWindow(cmd.id);
                        break;
                    case WindowAction::Focus:
                        focusWindow(cmd.id);
                        break;
                }
            }, Qt::QueuedConnection);
        });
    }
}

void WindowManager::stop() {
    if (bus) {
        bus->unsubscribe(tokenRequest);
    }
}

void WindowManager::shutdown() {
    stop();
    for (auto &pair : windows) {
        if (pair.second) {
            delete pair.second;
        }
    }
    windows.clear();
}

void WindowManager::setEngine(QQmlApplicationEngine *engine) {
    qmlEngine = engine;
}

void WindowManager::showWindow(WindowId id) {
    if (!qmlEngine) {
        return;
    }
    QObject *win = nullptr;
    auto it = windows.find(id);
    if (it == windows.end()) {
        win = WindowFactory::createWindow(id, qmlEngine, this);
        if (win) {
            windows[id] = win;
        }
    } else {
        win = it->second;
    }
    if (win) {
        win->setProperty("visible", true);
        QMetaObject::invokeMethod(win, "raise");
        QMetaObject::invokeMethod(win, "requestActivate");
    }
}

void WindowManager::closeWindow(WindowId id) {
    auto it = windows.find(id);
    if (it != windows.end() && it->second) {
        it->second->setProperty("visible", false);
    }
}

void WindowManager::focusWindow(WindowId id) {
    auto it = windows.find(id);
    if (it != windows.end() && it->second) {
        QMetaObject::invokeMethod(it->second, "raise");
        QMetaObject::invokeMethod(it->second, "requestActivate");
    }
}

void WindowManager::toggleWindow(WindowId id) {
    auto it = windows.find(id);
    if (it != windows.end() && it->second) {
        bool vis = it->second->property("visible").toBool();
        it->second->setProperty("visible", !vis);
        if (!vis) {
            QMetaObject::invokeMethod(it->second, "raise");
            QMetaObject::invokeMethod(it->second, "requestActivate");
        }
    } else {
        showWindow(id);
    }
}
