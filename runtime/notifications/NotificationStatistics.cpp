#include "NotificationStatistics.h"
#include "../../runtime/events/RuntimeEvent.h"

namespace swm::runtime::notifications {

NotificationStatistics::NotificationStatistics(std::shared_ptr<IEventBus> eventBus, QObject* parent)
    : QObject(parent), bus(std::move(eventBus)) {
}

NotificationStatistics::~NotificationStatistics() {
    shutdown();
}

void NotificationStatistics::initialize() {
    if (bus) {
        eventToken = bus->subscribe(
            RuntimeEvent::NotificationChanged,
            [this](const std::any& payload) { this->onNotificationChanged(payload); }
        );
    }
}

void NotificationStatistics::start() {}
void NotificationStatistics::stop() {}

void NotificationStatistics::shutdown() {
    if (bus && eventToken.id != 0) {
        bus->unsubscribe(eventToken);
        eventToken.id = 0;
    }
}

void NotificationStatistics::onNotificationChanged(const std::any& payload) {
    if (payload.type() != typeid(NotificationSnapshot)) return;
    
    auto snapshot = std::any_cast<NotificationSnapshot>(payload);
    
    std::lock_guard<std::mutex> lock(statsMutex);
    
    auto it = knownStates.find(snapshot.id);
    if (it != knownStates.end()) {
        const auto& oldState = it->second;
        
        if (!oldState.isRead) unread--;
        if (oldState.lifecycle == NotificationLifecycle::Active) active--;
        if (oldState.lifecycle == NotificationLifecycle::Dismissed) dismissed--;
        
        if (oldState.severity == NotificationSeverity::Warning) warning--;
        if (oldState.severity == NotificationSeverity::Error) error--;
        if (oldState.severity == NotificationSeverity::Critical) critical--;
        
    } else {
        total++;
    }
    
    if (snapshot.lifecycle == NotificationLifecycle::Archived) {
        knownStates.erase(snapshot.id);
        total--;
    } else {
        if (!snapshot.isRead) unread++;
        if (snapshot.lifecycle == NotificationLifecycle::Active) active++;
        if (snapshot.lifecycle == NotificationLifecycle::Dismissed) dismissed++;
        
        if (snapshot.severity == NotificationSeverity::Warning) warning++;
        if (snapshot.severity == NotificationSeverity::Error) error++;
        if (snapshot.severity == NotificationSeverity::Critical) critical++;
        
        knownStates[snapshot.id] = {snapshot.lifecycle, snapshot.severity, snapshot.isRead};
    }
    
    emit statisticsChanged();
}

int NotificationStatistics::getTotal() const { std::lock_guard<std::mutex> lock(statsMutex); return total; }
int NotificationStatistics::getUnread() const { std::lock_guard<std::mutex> lock(statsMutex); return unread; }
int NotificationStatistics::getActive() const { std::lock_guard<std::mutex> lock(statsMutex); return active; }
int NotificationStatistics::getDismissed() const { std::lock_guard<std::mutex> lock(statsMutex); return dismissed; }
int NotificationStatistics::getWarning() const { std::lock_guard<std::mutex> lock(statsMutex); return warning; }
int NotificationStatistics::getError() const { std::lock_guard<std::mutex> lock(statsMutex); return error; }
int NotificationStatistics::getCritical() const { std::lock_guard<std::mutex> lock(statsMutex); return critical; }

} // namespace swm::runtime::notifications
