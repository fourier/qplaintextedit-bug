cmake_minimum_required(VERSION 3.1.0)

project(qbug VERSION 1.0.0 LANGUAGES CXX)

SET(CMAKE_COLOR_MAKEFILE OFF)
SET(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5  COMPONENTS Core Gui Widgets REQUIRED)

add_executable(qbug
    qbug.cpp
    )

target_link_libraries(qbug Qt5::Core Qt5::Gui Qt5::Widgets)
