cmake_minimum_required(VERSION 3.16)
project(SwDeskApp VERSION 1.0.0 LANGUAGES CXX OBJCXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

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
)

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
)

if(APPLE)
    target_link_libraries(SwDeskApp PRIVATE ${COCOA_LIBRARY})
endif()
