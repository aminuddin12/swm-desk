#pragma once
#include <cstdint>

namespace swm::runtime::tasks {

enum class RetentionRule {
    RemoveImmediately,
    KeepCompleted,
    KeepFailed
};

struct TaskRetentionPolicy {
    RetentionRule rule{RetentionRule::KeepCompleted};
    std::uint32_t maximumHistory{100};
};

}
