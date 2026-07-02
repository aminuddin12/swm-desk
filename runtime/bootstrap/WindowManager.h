#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "../../core/contracts/IRuntimeService.h"
#include "../../core/contracts/IEventBus.h"
#include "WindowId.h"
#include <memory>
#include <unordered_map>

class WindowManager : public QObject, public IRuntimeService {
    Q_OBJECT

public:
    explicit WindowManager(std::shared_ptr<IEventBus> eventBus, QObject *parent = nullptr);
    ~WindowManager() override;

    void initialize() override;
    void start() override;
    void stop() override;
    void shutdown() override;

    void setEngine(QQmlApplicationEngine *engine);
    
    void showWindow(WindowId id);
    void closeWindow(WindowId id);
    void focusWindow(WindowId id);
    void toggleWindow(WindowId id);

private:
    std::shared_ptr<IEventBus> bus;
    SubscriptionToken tokenRequest;
    QQmlApplicationEngine *qmlEngine = nullptr;
    std::unordered_map<WindowId, QObject*> windows;
};

#endif
