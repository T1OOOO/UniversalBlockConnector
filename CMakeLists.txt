cmake_minimum_required(VERSION 3.14)

project(UniversalBlockConnector LANGUAGES CXX)

set(QT_CREATOR_SKIP_PACKAGE_MANAGER_SETUP ON)
set(QT_CREATOR_SKIP_CONAN_SETUP ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

add_subdirectory(src/utils)
add_subdirectory(src/blocks/common)
add_subdirectory(src/blocks/sources)
add_subdirectory(src/blocks/interfaces)
add_subdirectory(src/blocks/modyfiers)
add_subdirectory(src/blocks/viewers)

#add_subdirectory(src/blocks/struct)
#add_subdirectory(src/Protocol)
#add_subdirectory(src/script)

add_subdirectory(3rdparty/nodeeditor)
add_subdirectory(3rdparty/Log4Qt)
#add_subdirectory(3rdparty/libcrc)
#add_subdirectory(3rdparty/bitfield-c)
#add_subdirectory(3rdparty/ChaiScript)
#add_subdirectory(3rdparty/ChaiScript_Extras)

include(GNUInstallDirs)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/blocks)

add_executable(UniversalBlockConnector
    src/gui/mainwindow.h
    src/gui/mainwindow.cpp
    src/main.cpp
)

target_link_libraries(UniversalBlockConnector Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets nodes UBCSources UBCInterfaces
    UBCModyfiers UBCViewers UBCUtils log4qt )
#UBCStruct crc bitfield-c

