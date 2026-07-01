#include <obs-module.h>
#include <obs-source.h>

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("sw-desk", "en-US")

extern struct obs_source_info lowerThirdsSourceInfo;
extern void startWebSocketServer(void);
extern void stopWebSocketServer(void);

bool obs_module_load(void) {
    startWebSocketServer();
    obs_register_source_s(&lowerThirdsSourceInfo, 408);
    return true;
}

void obs_module_unload(void) {
    stopWebSocketServer();
}
