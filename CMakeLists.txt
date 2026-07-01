cmake_minimum_required(VERSION 3.16)
project(SwDeskApp VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Quick QuickControls2 Widgets Sql Svg REQUIRED)

add_executable(SwDeskApp
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
)

target_link_libraries(SwDeskApp PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    Qt6::Widgets
    Qt6::Sql
    Qt6::Svg
)
