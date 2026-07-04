#ifndef GRAPHICSFRAMESNAPSHOT_H
#define GRAPHICSFRAMESNAPSHOT_H

#include <memory>
#include <cstdint>

namespace swm::graphics { class Frame; }

namespace swm::runtime::graphics {

struct GraphicsFrameSnapshot {
    std::shared_ptr<const swm::graphics::Frame> frame;
    uint64_t renderDurationNs;
    uint64_t sequenceNumber;
    uint64_t timestampNs;
};

}

#endif
