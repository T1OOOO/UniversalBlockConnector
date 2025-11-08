cmake_minimum_required(VERSION 3.14)

project(UniversalBlockConnector LANGUAGES CXX)

# Option to generate compile_commands.json (useful for IDEs and clangd)
# Can be disabled with: cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=OFF
option(ENABLE_COMPILE_COMMANDS "Generate compile_commands.json for clangd and IDEs" ON)
if(ENABLE_COMPILE_COMMANDS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

set(QT_CREATOR_SKIP_PACKAGE_MANAGER_SETUP ON)
set(QT_CREATOR_SKIP_CONAN_SETUP ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Charts)

add_subdirectory(src/utils)
add_subdirectory(src/blocks/common)
add_subdirectory(src/blocks/sources)
add_subdirectory(src/blocks/interfaces)
add_subdirectory(src/blocks/modyfiers)
add_subdirectory(src/blocks/viewers)
add_subdirectory(src/blocks/struct)

#add_subdirectory(src/blocks/struct)
#add_subdirectory(src/protocol)
#add_subdirectory(src/script)

add_subdirectory(3rdparty/nodeeditor)
# Create alias 'nodes' for QtNodes for backward compatibility
if(TARGET QtNodes AND NOT TARGET nodes)
    add_library(nodes ALIAS QtNodes)
endif()
add_subdirectory(3rdparty/Log4Qt)
add_subdirectory(3rdparty/qbinarizer)
#add_subdirectory(3rdparty/libcrc)
#add_subdirectory(3rdparty/bitfield-c)
#add_subdirectory(3rdparty/ChaiScript)
#add_subdirectory(3rdparty/ChaiScript_Extras)

include(GNUInstallDirs)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/qbinarizer/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/blocks)

add_executable(UniversalBlockConnector
    ${jsonmodel_sources}
    src/gui/mainwindow.h
    src/gui/mainwindow.cpp
    src/main.cpp
)

target_link_libraries(UniversalBlockConnector Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts nodes UBCSources UBCInterfaces
    UBCModyfiers  UBCViewers UBCUtils UBCStructs log4qt qbinarizer::qbinarizer) #
#UBCStruct crc bitfield-c

