#pragma once

namespace swm::runtime::tasks {

enum class TaskState {
    Pending,
    Running,
    Completed,
    Failed,
    Cancelled,
    Paused
};

}
