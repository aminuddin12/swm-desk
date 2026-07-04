#ifndef GRAPHICSENGINESERVICE_H
#define GRAPHICSENGINESERVICE_H

#include <memory>
#include <string>
#include <cstdint>

namespace swm::graphics {
class GraphicsEngine;
class Canvas;
class Frame;
enum class EngineBackend;
}

namespace swm::runtime::graphics {

class GraphicsEngineService {
public:
    GraphicsEngineService(uint32_t width, uint32_t height);
    ~GraphicsEngineService();

    void initialize();
    void shutdown();

    std::shared_ptr<const swm::graphics::Frame> render(
        const std::shared_ptr<swm::graphics::Canvas>& canvas);

    std::string getBackendName() const;
    std::string getEngineVersion() const;
    uint32_t getWidth() const;
    uint32_t getHeight() const;

private:
    uint32_t m_width;
    uint32_t m_height;
    std::unique_ptr<swm::graphics::GraphicsEngine> m_engine;
};

}

#endif
