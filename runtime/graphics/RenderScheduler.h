#ifndef RENDERSCHEDULER_H
#define RENDERSCHEDULER_H

#include "contracts/RenderSessionId.h"
#include <cstdint>

namespace swm::runtime::graphics {

class RenderScheduler {
public:
    RenderScheduler() = default;
    ~RenderScheduler() = default;

    void scheduleOnce(RenderSessionId sessionId, uint64_t delayMs);
    void scheduleRepeating(RenderSessionId sessionId, uint64_t intervalMs);
    void cancel(RenderSessionId sessionId);
    void cancelAll();
};

}

#endif
