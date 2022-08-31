project(UBCModyfiers)

set(source_path ${UBCModyfiers_SOURCE_DIR})

set(modyfiers_headers
    #Delay
    delay/delaycontroller.h
    delay/delaywidget.h
    delay/delaydatamodel.h

    #Lost
    lost/lostcontroller.h
    lost/lostdatamodel.h
    lost/lostwidget.h
)

set(modyfiers_sources
    #Delay
    delay/delaycontroller.cpp
    delay/delaywidget.cpp
    delay/delaydatamodel.cpp

    #Lost
    lost/lostcontroller.cpp
    lost/lostdatamodel.cpp
    lost/lostwidget.cpp
)

set(sources
    ${modyfiers_headers}
    ${modyfiers_sources}
)

source_group(TREE ${source_path} FILES ${sources})

add_library(UBCModyfiers STATIC)
target_sources(UBCModyfiers PRIVATE ${sources})

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
#find_package(nodes)

target_link_libraries(UBCModyfiers UBCCommon Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets nodes log4qt)

#target_compile_definitions(UBCModyfiers
#  PUBLIC
#    NODE_EDITOR_SHARED
#  PRIVATE
#    NODE_EDITOR_EXPORTS
#    #NODE_DEBUG_DRAWING
#    #QT_NO_KEYWORDS
#)

