project(UBCSources)

set(source_path ${UBCSources_SOURCE_DIR})

set(sources_headers
    #Sender
    datasender/datasendercontroller.h
    datasender/datasenderwidget.h
    datasender/datasendermodel.h)

set(sources_sources
    #Sender
    datasender/datasendercontroller.cpp
    datasender/datasenderwidget.cpp
    datasender/datasendermodel.cpp)

set(sources
    ${sources_headers}
    ${sources_sources}
)

source_group(TREE ${source_path} FILES ${sources})

add_library(UBCSources STATIC)
target_sources(UBCSources PRIVATE ${sources})

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
#find_package(nodes)

target_link_libraries(UBCSources UBCCommon Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets nodes)

#target_compile_definitions(UBCSources
#  PUBLIC
#    NODE_EDITOR_SHARED
#  PRIVATE
#    NODE_EDITOR_EXPORTS
#    #NODE_DEBUG_DRAWING
#    #QT_NO_KEYWORDS
#)

