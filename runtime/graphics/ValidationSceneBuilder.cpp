#include "ValidationSceneBuilder.h"
#include <swm/scene/Canvas.h>
#include <swm/scene/Scene.h>
#include <swm/scene/Layer.h>
#include <swm/math/Color.h>
#include <swm/math/Size.h>

namespace swm::runtime::graphics {

std::shared_ptr<swm::graphics::Canvas> ValidationSceneBuilder::build() {
    auto canvas = std::make_shared<swm::graphics::Canvas>();

    swm::graphics::Size size;
    size.width = 1920.0f;
    size.height = 1080.0f;
    canvas->setSize(size);

    swm::graphics::Color clearColor;
    clearColor.r = 30.0f / 255.0f;
    clearColor.g = 30.0f / 255.0f;
    clearColor.b = 30.0f / 255.0f;
    clearColor.a = 1.0f;
    canvas->setClearColor(clearColor);

    auto scene = std::make_shared<swm::graphics::Scene>();
    auto backgroundLayer = std::make_shared<swm::graphics::Layer>();
    backgroundLayer->setOpacity(1.0f);
    backgroundLayer->setVisible(true);
    scene->addLayer(backgroundLayer);

    canvas->setScene(scene);

    return canvas;
}

}
