#ifndef SERVICEID_H
#define SERVICEID_H

namespace swm::runtime::notifications {

enum class ServiceId {
    Runtime,
    Downloader,
    Marketplace,
    OBS,
    Updater,
    PluginManager,
    AI
};

} // namespace swm::runtime::notifications

#endif
