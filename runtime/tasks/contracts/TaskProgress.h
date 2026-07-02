#pragma once
#include <cstdint>

namespace swm::runtime::tasks {

struct TaskProgress {
    std::uint8_t percent{0};
    std::uint64_t currentValue{0};
    std::uint64_t maximumValue{0};
};

}
