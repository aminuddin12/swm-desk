#include "GraphicsEngineService.h"
#include <swm/GraphicsEngine.h>
#include <swm/EngineConfiguration.h>
#include <swm/EngineBackend.h>
#include <swm/EngineVersion.h>
#include <swm/Frame.h>
#include <swm/scene/Canvas.h>

namespace swm::runtime::graphics {

GraphicsEngineService::GraphicsEngineService(uint32_t width, uint32_t height)
    : m_width(width), m_height(height) {
}

GraphicsEngineService::~GraphicsEngineService() {
    shutdown();
}

void GraphicsEngineService::initialize() {
    swm::graphics::EngineConfiguration config;
    config.width = m_width;
    config.height = m_height;
    config.backend = swm::graphics::EngineBackend::Null;
    config.pixelFormat = swm::graphics::PixelFormat::RGBA8;

    m_engine = std::make_unique<swm::graphics::GraphicsEngine>(config);
    m_engine->initialize();
    m_engine->start();
}

void GraphicsEngineService::shutdown() {
    if (m_engine) {
        m_engine->stop();
        m_engine->shutdown();
        m_engine.reset();
    }
}

std::shared_ptr<const swm::graphics::Frame> GraphicsEngineService::render(
    const std::shared_ptr<swm::graphics::Canvas>& canvas) {
    if (!m_engine) {
        return nullptr;
    }
    return m_engine->render(canvas);
}

std::string GraphicsEngineService::getBackendName() const {
    return "Null";
}

std::string GraphicsEngineService::getEngineVersion() const {
    return swm::graphics::EngineVersion::getVersionString();
}

uint32_t GraphicsEngineService::getWidth() const {
    return m_width;
}

uint32_t GraphicsEngineService::getHeight() const {
    return m_height;
}

}
