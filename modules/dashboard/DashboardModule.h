#ifndef DASHBOARDMODULE_H
#define DASHBOARDMODULE_H

#include "../../core/contracts/IModule.h"

class DashboardModule : public IModule {
public:
    DashboardModule() = default;
    ~DashboardModule() = default;
    std::string name() const override;
    void initialize() override;
    void shutdown() override;
};

#endif
