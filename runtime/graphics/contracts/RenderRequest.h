#ifndef RENDERREQUEST_H
#define RENDERREQUEST_H

#include <memory>
#include <cstdint>
#include <swm/PixelFormat.h>
#include <swm/math/Color.h>

namespace swm::scene { class Document; }

namespace swm::runtime::graphics {

enum class RenderOutputType {
    Preview,
    Thumbnail,
    ExportPng,
    ExportJpeg,
    ObsSource,
    VideoFrame
};

struct RenderRequest {
    std::shared_ptr<swm::scene::Document> document;
    uint32_t width = 1920;
    uint32_t height = 1080;
    RenderOutputType outputType = RenderOutputType::Preview;
    swm::graphics::PixelFormat pixelFormat = swm::graphics::PixelFormat::RGBA8;
    swm::math::Color backgroundColor;
    bool clearBeforeRender = true;
    uint32_t targetFps = 30;
    float renderScale = 1.0f;
};

}

#endif
