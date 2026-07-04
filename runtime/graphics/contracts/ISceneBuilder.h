#ifndef ISCENEBUILDER_H
#define ISCENEBUILDER_H

#include <memory>

namespace swm::scene { class Document; }

namespace swm::runtime::graphics {

class ISceneBuilder {
public:
    virtual ~ISceneBuilder() = default;
    virtual std::shared_ptr<swm::scene::Document> build() = 0;
};

}

#endif
