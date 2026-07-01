cmake_minimum_required(VERSION 3.12)
project(lower-thirds-plugin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(obs-studio/libobs)
include_directories(/usr/local/include)

add_library(swmpluginlib MODULE
    plugin-main.cpp
    lower-thirds-source.cpp
)

target_link_libraries(swmpluginlib PRIVATE
    "/Applications/OBS.app/Contents/Frameworks/libobs.framework/libobs"
    sqlite3
)

set_target_properties(swmpluginlib PROPERTIES
    PREFIX ""
    SUFFIX ".so"
)
