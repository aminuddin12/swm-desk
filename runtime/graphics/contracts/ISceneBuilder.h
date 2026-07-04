#ifndef ISCENEBUILDER_H
#define ISCENEBUILDER_H

#include <memory>

namespace swm::graphics { class Canvas; }

namespace swm::runtime::graphics {

class ISceneBuilder {
public:
    virtual ~ISceneBuilder() = default;
    virtual std::shared_ptr<swm::graphics::Canvas> build() = 0;
};

}

#endif
