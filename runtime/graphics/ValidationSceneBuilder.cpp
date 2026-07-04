#include "ValidationSceneBuilder.h"
#include <swm/scene/Document.h>
#include <swm/scene/Stage.h>
#include <swm/scene/Canvas.h>
#include <swm/scene/Scene.h>
#include <swm/scene/Layer.h>
#include <swm/scene/RectangleNode.h>
#include <swm/math/Color.h>
#include <swm/math/Size.h>
#include <swm/math/Transform.h>

namespace swm::runtime::graphics {

std::shared_ptr<swm::scene::Document> ValidationSceneBuilder::build() {
    auto document = std::make_shared<swm::scene::Document>();
    document->setName("Validation Project");

    auto stage = std::make_shared<swm::scene::Stage>();
    stage->setName("Main Stage");

    auto canvas = std::make_shared<swm::scene::Canvas>();
    swm::math::Size size{1920.0f, 1080.0f};
    canvas->setSize(size);
    canvas->setClearColor(swm::math::Color{30, 30, 30, 255}); // Dark gray

    auto scene = std::make_shared<swm::scene::Scene>();
    auto backgroundLayer = std::make_shared<swm::scene::Layer>();

    auto rectNode = std::make_shared<swm::scene::RectangleNode>();
    rectNode->setSize(swm::math::Size{400.0f, 300.0f});
    rectNode->setFillColor(swm::math::Color{200, 50, 50, 255}); // Red rectangle
    
    // Position the rectangle at (100, 100)
    swm::math::Transform transform;
    transform.translation.x = 100.0f;
    transform.translation.y = 100.0f;
    rectNode->setTransform(transform);

    backgroundLayer->addChild(rectNode);
    scene->addLayer(backgroundLayer);
    canvas->setScene(scene);
    
    stage->addCanvas(canvas);
    document->addStage(stage);

    return document;
}

} // namespace swm::runtime::graphics
