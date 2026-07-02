#if SWM_ENABLE_RUNTIME_DIAGNOSTICS

#include "RuntimeDiagnostics.h"
#include <chrono>

namespace swm::runtime::diagnostics {

RuntimeDiagnostics::RuntimeDiagnostics(
    std::shared_ptr<ILogger> logger,
    std::shared_ptr<IEventBus> eventBus,
    std::shared_ptr<tasks::TaskService> taskService,
    std::shared_ptr<tasks::TaskRepository> taskRepo,
    std::shared_ptr<notifications::NotificationService> notifService,
    std::shared_ptr<notifications::NotificationRepository> notifRepo
) : logger(std::move(logger)), bus(std::move(eventBus)),
    taskService(std::move(taskService)), taskRepo(std::move(taskRepo)),
    notifService(std::move(notifService)), notifRepo(std::move(notifRepo)) {
}

RuntimeDiagnostics::~RuntimeDiagnostics() {
    shutdown();
}

void RuntimeDiagnostics::initialize() {
}

void RuntimeDiagnostics::start() {
    isRunning = true;
    diagnosticsThread = std::thread([this]() {
        std::this_thread::sleep_for(std::chrono::seconds(2)); // wait for UI to load
        if (!isRunning) return;

        logger->info("Starting Runtime Diagnostics...", LogCategory::Runtime);

        runTaskLifetimeTest();
        runTaskLongRunningTest();
        
        runNotificationLifetimeTest();
        runNotificationLongRunningTest();

        logger->info("Runtime Diagnostics Completed Successfully.", LogCategory::Runtime);
    });
}

void RuntimeDiagnostics::stop() {
    isRunning = false;
    if (diagnosticsThread.joinable()) {
        diagnosticsThread.join();
    }
}

void RuntimeDiagnostics::shutdown() {
    stop();
}

void RuntimeDiagnostics::runTaskLifetimeTest() {
    logger->info("[DIAGNOSTICS] Task Lifetime Test - 100K iterations", LogCategory::Runtime);
    for (int i = 0; i < 100000; ++i) {
        if (!isRunning) break;
        auto handle = taskService->createTask("LifetimeTest", tasks::TaskCategory::System);
        handle.complete();
        taskRepo->erase(handle.getId());
    }
    logger->info("[DIAGNOSTICS] Task Lifetime Test Done. Pending in Repo: " + std::to_string(taskRepo->getAll().size()), LogCategory::Runtime);
}

void RuntimeDiagnostics::runTaskLongRunningTest() {
    logger->info("[DIAGNOSTICS] Task Long Running Test - 1M progress updates", LogCategory::Runtime);
    auto handle = taskService->createTask("LongRunningTest", tasks::TaskCategory::System);
    for (int i = 0; i < 1000000; ++i) {
        if (!isRunning) break;
        handle.progress(i % 100, i, 1000000);
    }
    handle.complete();
    logger->info("[DIAGNOSTICS] Task Long Running Test Done.", LogCategory::Runtime);
}

void RuntimeDiagnostics::runNotificationLifetimeTest() {
    logger->info("[DIAGNOSTICS] Notification Lifetime Test - 100K iterations", LogCategory::Runtime);
    for (int i = 0; i < 100000; ++i) {
        if (!isRunning) break;
        auto handle = notifService->notifyInfo(notifications::ServiceId::Runtime, notifications::NotificationCategory::System, "Test", "Msg");
        handle.dismiss();
        notifRepo->erase(handle.getId());
    }
    logger->info("[DIAGNOSTICS] Notification Lifetime Test Done. Pending in Repo: " + std::to_string(notifRepo->count()), LogCategory::Runtime);
}

void RuntimeDiagnostics::runNotificationLongRunningTest() {
    logger->info("[DIAGNOSTICS] Notification Long Running Test - 1M state mutations", LogCategory::Runtime);
    auto handle = notifService->notifyInfo(notifications::ServiceId::Runtime, notifications::NotificationCategory::System, "LongTest", "Starting...");
    for (int i = 0; i < 1000000; ++i) {
        if (!isRunning) break;
        handle.updateMessage("Msg " + std::to_string(i));
    }
    handle.dismiss();
    logger->info("[DIAGNOSTICS] Notification Long Running Test Done.", LogCategory::Runtime);
}

} // namespace swm::runtime::diagnostics

#endif // SWM_ENABLE_RUNTIME_DIAGNOSTICS
