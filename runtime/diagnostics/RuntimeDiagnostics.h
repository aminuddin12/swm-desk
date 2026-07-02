#ifndef RUNTIMEDIAGNOSTICS_H
#define RUNTIMEDIAGNOSTICS_H

#if SWM_ENABLE_RUNTIME_DIAGNOSTICS

#include "../../core/contracts/IRuntimeService.h"
#include "../../core/contracts/IEventBus.h"
#include "../logging/Logger.h"
#include "../tasks/TaskService.h"
#include "../tasks/TaskRepository.h"
#include "../notifications/NotificationService.h"
#include "../notifications/NotificationRepository.h"
#include <memory>
#include <thread>
#include <atomic>

namespace swm::runtime::diagnostics {

class RuntimeDiagnostics : public IRuntimeService {
public:
    RuntimeDiagnostics(
        std::shared_ptr<ILogger> logger,
        std::shared_ptr<IEventBus> eventBus,
        std::shared_ptr<tasks::TaskService> taskService,
        std::shared_ptr<tasks::TaskRepository> taskRepo,
        std::shared_ptr<notifications::NotificationService> notifService,
        std::shared_ptr<notifications::NotificationRepository> notifRepo
    );
    ~RuntimeDiagnostics() override;

    void initialize() override;
    void start() override;
    void stop() override;
    void shutdown() override;

private:
    void runTaskLifetimeTest();
    void runTaskLongRunningTest();
    void runNotificationLifetimeTest();
    void runNotificationLongRunningTest();

    std::shared_ptr<ILogger> logger;
    std::shared_ptr<IEventBus> bus;
    std::shared_ptr<tasks::TaskService> taskService;
    std::shared_ptr<tasks::TaskRepository> taskRepo;
    std::shared_ptr<notifications::NotificationService> notifService;
    std::shared_ptr<notifications::NotificationRepository> notifRepo;

    std::atomic<bool> isRunning{false};
    std::thread diagnosticsThread;
};

} // namespace swm::runtime::diagnostics

#endif // SWM_ENABLE_RUNTIME_DIAGNOSTICS

#endif
