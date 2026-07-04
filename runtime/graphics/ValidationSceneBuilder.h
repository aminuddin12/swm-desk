#ifndef VALIDATIONSCENEBUILDER_H
#define VALIDATIONSCENEBUILDER_H

#include "contracts/ISceneBuilder.h"

namespace swm::runtime::graphics {

class ValidationSceneBuilder : public ISceneBuilder {
public:
    std::shared_ptr<swm::graphics::Canvas> build() override;
};

}

#endif
