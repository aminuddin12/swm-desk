#import "MacStatusBarService.h"
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#include "../LogEntry.h"
#include <QCoreApplication>
#include <QMetaObject>
#include "../../bootstrap/WindowId.h"

@interface MacStatusBarServiceHandler : NSObject
@property (assign) MacStatusBarService *service;
- (void)onQuit:(id)sender;
- (void)onClearLogs:(id)sender;
- (void)onOpenLogViewer:(id)sender;
@end

@implementation MacStatusBarServiceHandler
- (void)onQuit:(id)sender {
    (void)sender;
    QCoreApplication::quit();
}
- (void)onClearLogs:(id)sender {
    (void)sender;
    if (_service) {
        _service->publishClearLogs();
    }
}
- (void)onOpenLogViewer:(id)sender {
    (void)sender;
    if (_service) {
        _service->publishOpenLogViewer();
    }
}
@end

MacStatusBarService::MacStatusBarService(std::shared_ptr<IEventBus> eventBus)
    : bus(eventBus), statusItem(nullptr), menuHandler(nullptr) {
    recentLogs = {
        "20:00:12  [INFO]  Runtime  Application Started",
        "20:00:12  [INFO]  Runtime  Runtime Initialized",
        "20:00:12  [INFO]  Runtime  Logger Ready",
        "20:00:12  [INFO]  Runtime  Configuration Loaded",
        "20:00:12  [INFO]  Runtime  UI Started"
    };
}

MacStatusBarService::~MacStatusBarService() {
    shutdown();
}

void MacStatusBarService::initialize() {
    MacStatusBarServiceHandler *handler = [[MacStatusBarServiceHandler alloc] init];
    handler.service = this;
    menuHandler = (__bridge_retained void *)handler;

    dispatch_async(dispatch_get_main_queue(), ^{
        NSStatusItem *item = [[NSStatusBar systemStatusBar] statusItemWithLength:NSVariableStatusItemLength];
        item.button.title = @"⚡ SWM";
        statusItem = (__bridge_retained void *)item;
        updateMenu();
    });
}

void MacStatusBarService::start() {
    if (bus) {
        token = bus->subscribe(RuntimeEvent::LogAdded, [this](const std::any &payload) {
            auto entry = std::any_cast<std::shared_ptr<LogEntry>>(payload);
            QMetaObject::invokeMethod(QCoreApplication::instance(), [this, entry]() {
                std::string timeStr = entry->timestamp.size() >= 19 ? entry->timestamp.substr(11, 8) : entry->timestamp;
                std::string levelStr;
                switch (entry->level) {
                    case LogLevel::Trace: levelStr = "TRACE"; break;
                    case LogLevel::Debug: levelStr = "DEBUG"; break;
                    case LogLevel::Info: levelStr = "INFO"; break;
                    case LogLevel::Success: levelStr = "SUCCESS"; break;
                    case LogLevel::Warning: levelStr = "WARN"; break;
                    case LogLevel::Error: levelStr = "ERROR"; break;
                    case LogLevel::Critical: levelStr = "CRITICAL"; break;
                }
                std::string catStr;
                switch (entry->category) {
                    case LogCategory::Runtime: catStr = "Runtime"; break;
                    case LogCategory::OBS: catStr = "OBS"; break;
                    case LogCategory::UI: catStr = "UI"; break;
                    case LogCategory::Plugin: catStr = "Plugin"; break;
                    case LogCategory::Marketplace: catStr = "Marketplace"; break;
                }
                std::string logMsg = timeStr + "  [" + levelStr + "]  " + catStr + "  " + entry->message;
                onLogAdded(logMsg);
            }, Qt::QueuedConnection);
        });

        tokenCleared = bus->subscribe(RuntimeEvent::MemoryLogsCleared, [this](const std::any &payload) {
            (void)payload;
            QMetaObject::invokeMethod(QCoreApplication::instance(), [this]() {
                recentLogs.clear();
                updateMenu();
            }, Qt::QueuedConnection);
        });
    }
}

void MacStatusBarService::stop() {
    if (bus) {
        bus->unsubscribe(token);
        bus->unsubscribe(tokenCleared);
    }
}

void MacStatusBarService::shutdown() {
    stop();
    if (statusItem) {
        NSStatusItem *item = (__bridge_transfer NSStatusItem *)statusItem;
        [[NSStatusBar systemStatusBar] removeStatusItem:item];
        statusItem = nullptr;
    }
    if (menuHandler) {
        MacStatusBarServiceHandler *handler = (__bridge_transfer MacStatusBarServiceHandler *)menuHandler;
        (void)handler;
        menuHandler = nullptr;
    }
}

void MacStatusBarService::publishClearLogs() {
    if (bus) {
        bus->publish(RuntimeEvent::ClearMemoryLogs, std::any());
    }
}

void MacStatusBarService::publishOpenLogViewer() {
    if (bus) {
        bus->publish(RuntimeEvent::WindowRequest, WindowCommand{WindowId::LogViewer, WindowAction::Show});
    }
}

void MacStatusBarService::onLogAdded(const std::string &logMessage) {
    if (recentLogs.size() >= 5) {
        recentLogs.erase(recentLogs.begin());
    }
    recentLogs.push_back(logMessage);
    updateMenu();
}

void MacStatusBarService::updateMenu() {
    if (!statusItem) {
        return;
    }

    NSStatusItem *item = (__bridge NSStatusItem *)statusItem;
    NSMenu *menu = [[NSMenu alloc] init];

    NSMenuItem *titleItem = [[NSMenuItem alloc] initWithTitle:@"⚡ SWM Runtime" action:nil keyEquivalent:@""];
    [titleItem setEnabled:NO];
    [menu addItem:titleItem];

    NSMenuItem *statusItemRow = [[NSMenuItem alloc] initWithTitle:@"Status: 🟢 Running" action:nil keyEquivalent:@""];
    [statusItemRow setEnabled:NO];
    [menu addItem:statusItemRow];

    [menu addItem:[NSMenuItem separatorItem]];

    NSMenuItem *logsTitle = [[NSMenuItem alloc] initWithTitle:@"Recent Logs" action:nil keyEquivalent:@""];
    [logsTitle setEnabled:NO];
    [menu addItem:logsTitle];

    for (const auto &logStr : recentLogs) {
        NSString *nsStr = [NSString stringWithUTF8String:logStr.c_str()];
        NSMenuItem *logItem = [[NSMenuItem alloc] initWithTitle:nsStr action:nil keyEquivalent:@""];
        [logItem setEnabled:NO];
        [menu addItem:logItem];
    }

    [menu addItem:[NSMenuItem separatorItem]];

    MacStatusBarServiceHandler *handler = (__bridge MacStatusBarServiceHandler *)menuHandler;

    NSMenuItem *openLogViewerItem = [[NSMenuItem alloc] initWithTitle:@"Open Log Viewer" action:@selector(onOpenLogViewer:) keyEquivalent:@""];
    openLogViewerItem.target = handler;
    [menu addItem:openLogViewerItem];

    NSMenuItem *clearLogsItem = [[NSMenuItem alloc] initWithTitle:@"Clear Memory Logs" action:@selector(onClearLogs:) keyEquivalent:@""];
    clearLogsItem.target = handler;
    [menu addItem:clearLogsItem];

    [menu addItem:[NSMenuItem separatorItem]];

    NSMenuItem *quitItem = [[NSMenuItem alloc] initWithTitle:@"Quit SWM Desk" action:@selector(onQuit:) keyEquivalent:@"q"];
    quitItem.target = handler;
    [menu addItem:quitItem];

    item.menu = menu;
}
