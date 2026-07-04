#ifndef GRAPHICSRESOURCESERVICE_H
#define GRAPHICSRESOURCESERVICE_H

#include "contracts/IGraphicsResourceService.h"

namespace swm::runtime::graphics {

class GraphicsResourceService : public IGraphicsResourceService {
public:
    GraphicsResourceService() = default;
    ~GraphicsResourceService() override = default;
};

}

#endif
