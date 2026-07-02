#pragma once

#include "TaskId.h"
#include "TaskState.h"
#include "TaskCategory.h"
#include "TaskProgress.h"
#include <string>
#include <chrono>

namespace swm::runtime::tasks {

struct TaskSnapshot {
    TaskId id{0};
    std::string name;
    TaskCategory category{TaskCategory::Runtime};
    TaskState state{TaskState::Pending};
    TaskProgress progress;
    std::string message;
    std::chrono::system_clock::time_point createdTime;
    std::chrono::system_clock::time_point startedTime;
    std::chrono::system_clock::time_point finishedTime;
};

}
