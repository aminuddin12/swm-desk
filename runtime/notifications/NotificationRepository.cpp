#include "NotificationRepository.h"
#include <algorithm>

namespace swm::runtime::notifications {

void NotificationRepository::insert(const NotificationSnapshot& snapshot) {
    std::lock_guard<std::mutex> lock(mutex);
    snapshots.push_back(snapshot);
}

void NotificationRepository::replace(const NotificationSnapshot& snapshot) {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = std::find_if(snapshots.begin(), snapshots.end(),
        [&snapshot](const NotificationSnapshot& s) { return s.id == snapshot.id; });
    
    if (it != snapshots.end()) {
        *it = snapshot;
    }
}

void NotificationRepository::erase(NotificationId id) {
    std::lock_guard<std::mutex> lock(mutex);
    snapshots.erase(
        std::remove_if(snapshots.begin(), snapshots.end(),
            [id](const NotificationSnapshot& s) { return s.id == id; }),
        snapshots.end()
    );
}

std::optional<NotificationSnapshot> NotificationRepository::tryFind(NotificationId id) const {
    std::lock_guard<std::mutex> lock(mutex);
    auto it = std::find_if(snapshots.begin(), snapshots.end(),
        [id](const NotificationSnapshot& s) { return s.id == id; });
    
    if (it != snapshots.end()) {
        return *it;
    }
    return std::nullopt;
}

std::vector<NotificationSnapshot> NotificationRepository::getAll() const {
    std::lock_guard<std::mutex> lock(mutex);
    return snapshots;
}

bool NotificationRepository::contains(NotificationId id) const {
    std::lock_guard<std::mutex> lock(mutex);
    return std::any_of(snapshots.begin(), snapshots.end(),
        [id](const NotificationSnapshot& s) { return s.id == id; });
}

size_t NotificationRepository::count() const {
    std::lock_guard<std::mutex> lock(mutex);
    return snapshots.size();
}

} // namespace swm::runtime::notifications
