#ifndef NOTIFICATIONREPOSITORY_H
#define NOTIFICATIONREPOSITORY_H

#include "../../core/contracts/IRuntimeService.h"
#include "contracts/NotificationSnapshot.h"
#include <mutex>
#include <vector>
#include <optional>
#include <unordered_map>

namespace swm::runtime::notifications {

class NotificationRepository : public IRuntimeService {
public:
    NotificationRepository() = default;
    ~NotificationRepository() override = default;

    void initialize() override {}
    void start() override {}
    void stop() override {}
    void shutdown() override {}

    void insert(const NotificationSnapshot& snapshot);
    void replace(const NotificationSnapshot& snapshot);
    void erase(NotificationId id);

    std::optional<NotificationSnapshot> tryFind(NotificationId id) const;
    std::vector<NotificationSnapshot> getAll() const;
    bool contains(NotificationId id) const;
    size_t count() const;

private:
    std::vector<NotificationSnapshot> snapshots;
    mutable std::mutex mutex;
};

} // namespace swm::runtime::notifications

#endif
