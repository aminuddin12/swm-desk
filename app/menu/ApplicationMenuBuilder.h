#ifndef APPLICATIONMENUBUILDER_H
#define APPLICATIONMENUBUILDER_H

#include <QMenuBar>
#include <memory>
#include "../../core/contracts/IEventBus.h"

class ApplicationMenuBuilder {
public:
    ApplicationMenuBuilder();
    ~ApplicationMenuBuilder();

    void build(std::shared_ptr<IEventBus> eventBus);
};

#endif
