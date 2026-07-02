#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>

enum class QueueFullPolicy {
    BlockProducer,
    DropOldest
};

template <typename T>
class BlockingQueue {
public:
    BlockingQueue(size_t maxCapacity = 10000, QueueFullPolicy policy = QueueFullPolicy::BlockProducer)
        : capacity(maxCapacity), queuePolicy(policy) {}

    void push(const T &item) {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (capacity > 0 && items.size() >= capacity) {
            if (queuePolicy == QueueFullPolicy::DropOldest) {
                if (!items.empty()) {
                    items.pop();
                }
            } else {
                condProducer.wait(lock, [this]() { return items.size() < capacity; });
            }
        }
        items.push(item);
        condConsumer.notify_one();
    }

    bool pop(T &item) {
        std::unique_lock<std::mutex> lock(queueMutex);
        condConsumer.wait(lock, [this]() { return !items.empty() || shutdownFlag; });
        if (items.empty() && shutdownFlag) {
            return false;
        }
        item = std::move(items.front());
        items.pop();
        condProducer.notify_one();
        return true;
    }

    template <typename Rep, typename Period>
    bool popTimeout(T &item, const std::chrono::duration<Rep, Period> &timeout) {
        std::unique_lock<std::mutex> lock(queueMutex);
        if (!condConsumer.wait_for(lock, timeout, [this]() { return !items.empty() || shutdownFlag; })) {
            return false;
        }
        if (items.empty() && shutdownFlag) {
            return false;
        }
        item = std::move(items.front());
        items.pop();
        condProducer.notify_one();
        return true;
    }

    void shutdown() {
        std::lock_guard<std::mutex> lock(queueMutex);
        shutdownFlag = true;
        condConsumer.notify_all();
        condProducer.notify_all();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lock(queueMutex);
        return items.size();
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(queueMutex);
        return items.empty();
    }

private:
    std::queue<T> items;
    mutable std::mutex queueMutex;
    std::condition_variable condConsumer;
    std::condition_variable condProducer;
    size_t capacity;
    QueueFullPolicy queuePolicy;
    bool shutdownFlag = false;
};

#endif
