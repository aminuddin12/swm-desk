cmake_minimum_required(VERSION 3.16)
project(SwDeskApp VERSION 1.0.0 LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_definitions(SWM_ENABLE_RUNTIME_DIAGNOSTICS=0)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

list(APPEND CMAKE_PREFIX_PATH "/Users/aminuddinadl/qt/6.5.3/macos")

find_package(Qt6 COMPONENTS Quick QuickControls2 Widgets Sql Svg REQUIRED)

set(SRC_FILES
    app/main.cpp
    app/AppBootstrap.cpp
    app/AppBootstrap.h
    application/services/ServiceRegistry.cpp
    application/services/ServiceRegistry.h
    application/services/ModuleManager.cpp
    application/services/ModuleManager.h
    packages/validator/PackageValidator.cpp
    packages/validator/PackageValidator.h
    plugins/manager/PluginManager.cpp
    plugins/manager/PluginManager.h
    modules/dashboard/DashboardModule.cpp
    modules/dashboard/DashboardModule.h
    runtime/events/EventBus.h
    runtime/events/EventBus.cpp
    runtime/configuration/Configuration.h
    runtime/configuration/Configuration.cpp
    runtime/environment/Environment.h
    runtime/environment/Environment.cpp
    runtime/logging/Logger.h
    runtime/logging/Logger.cpp
    runtime/logging/LoggerFacade.h
    runtime/logging/LoggerFacade.cpp
    runtime/logging/Formatter/TextFormatter.h
    runtime/logging/Formatter/TextFormatter.cpp
    runtime/logging/Formatter/ColoredFormatter.h
    runtime/logging/Formatter/ColoredFormatter.cpp
    runtime/logging/sinks/ConsoleSink.h
    runtime/logging/sinks/ConsoleSink.cpp
    runtime/logging/sinks/FileSink.h
    runtime/logging/sinks/FileSink.cpp
    runtime/logging/sinks/MemorySink.h
    runtime/logging/sinks/MemorySink.cpp
    runtime/logging/sinks/WindowOverlaySink.h
    runtime/logging/sinks/WindowOverlaySink.cpp
    runtime/bootstrap/RuntimeContext.h
    runtime/bootstrap/RuntimeContext.cpp
    runtime/bootstrap/RuntimeBootstrap.h
    runtime/bootstrap/RuntimeBootstrap.cpp
    runtime/logging/LogRepository.h
    runtime/logging/LogRepository.cpp
    runtime/logging/LogStatistics.h
    runtime/logging/LogStatistics.cpp
    runtime/logging/LogExportService.h
    runtime/logging/LogExportService.cpp
    runtime/logging/LogListModel.h
    runtime/logging/LogListModel.cpp
    runtime/bootstrap/WindowManager.h
    runtime/bootstrap/WindowManager.cpp
    runtime/bootstrap/WindowFactory.h
    runtime/bootstrap/WindowFactory.cpp
    app/menu/ApplicationMenuBuilder.h
    app/menu/ApplicationMenuBuilder.cpp
    runtime/tasks/contracts/TaskId.h
    runtime/tasks/contracts/TaskState.h
    runtime/tasks/contracts/TaskCategory.h
    runtime/tasks/contracts/TaskProgress.h
    runtime/tasks/contracts/TaskSnapshot.h
    runtime/tasks/contracts/TaskRetentionPolicy.h
    runtime/tasks/contracts/TaskHandle.h
    runtime/tasks/contracts/TaskHandle.cpp
    runtime/notifications/NotificationRepository.cpp
    runtime/notifications/NotificationService.cpp
    runtime/notifications/NotificationStatistics.cpp
    runtime/notifications/NotificationListModel.cpp
    runtime/notifications/contracts/NotificationHandle.cpp
    runtime/diagnostics/RuntimeDiagnostics.cpp
    runtime/tasks/TaskRepository.h
    runtime/tasks/TaskRepository.cpp
    runtime/tasks/TaskService.h
    runtime/tasks/TaskService.cpp
    runtime/tasks/TaskStatistics.h
    runtime/tasks/TaskStatistics.cpp
    runtime/tasks/TaskListModel.h
    runtime/tasks/TaskListModel.cpp
    
    runtime/graphics/contracts/GraphicsFrameSnapshot.h
    runtime/graphics/contracts/RenderRequest.h
    runtime/graphics/contracts/RenderSessionId.h
    runtime/graphics/contracts/ISceneBuilder.h
    runtime/graphics/contracts/IGraphicsResourceService.h
    runtime/graphics/RenderSession.h
    runtime/graphics/RenderSession.cpp
    runtime/graphics/RenderSessionManager.h
    runtime/graphics/RenderSessionManager.cpp
    runtime/graphics/RenderScheduler.h
    runtime/graphics/RenderScheduler.cpp
    runtime/graphics/GraphicsEngineService.h
    runtime/graphics/GraphicsEngineService.cpp
    runtime/graphics/ValidationSceneBuilder.h
    runtime/graphics/ValidationSceneBuilder.cpp
    runtime/graphics/GraphicsResourceService.h
    runtime/graphics/GraphicsResourceService.cpp
    runtime/graphics/GraphicsRuntime.h
    runtime/graphics/GraphicsRuntime.cpp
    runtime/graphics/GraphicsStatistics.h
    runtime/graphics/GraphicsStatistics.cpp
    runtime/graphics/GraphicsPreviewItem.h
    runtime/graphics/GraphicsPreviewItem.cpp
)

option(SWM_USE_INTERNAL_GRAPHICS_ENGINE "Use bundled graphics engine" ON)

if(SWM_USE_INTERNAL_GRAPHICS_ENGINE)
    add_subdirectory(core/engines/graphics)
else()
    find_package(swm_graphics_engine REQUIRED)
endif()

if(APPLE)
    list(APPEND SRC_FILES
        runtime/logging/sinks/MacStatusBarService.h
        runtime/logging/sinks/MacStatusBarService.mm
    )
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
endif()

add_executable(SwDeskApp ${SRC_FILES})

if(APPLE)
    set_source_files_properties(runtime/logging/sinks/MacStatusBarService.mm PROPERTIES COMPILE_FLAGS "-fobjc-arc")
endif()

target_link_libraries(SwDeskApp PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
    Qt6::Sql
    Qt6::Svg
    swm_graphics_engine
)

if(APPLE)
    target_link_libraries(SwDeskApp PRIVATE ${COCOA_LIBRARY})
endif()
