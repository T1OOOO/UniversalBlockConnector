project(UBCViewers)

set(source_path ${UBCViewers_SOURCE_DIR})

set(viewers_headers
    #Viewer
    dataviewer/dataviewercontroller.h
    dataviewer/dataviewerwidget.h
    dataviewer/dataviewermodel.h

    #Tmp
    tmp/tmpcontroller.h
    tmp/tmpwidget.h
    tmp/tmpmodel.h
)

set(viewers_sources
    #Viewer
    dataviewer/dataviewercontroller.cpp
    dataviewer/dataviewerwidget.cpp
    dataviewer/dataviewermodel.cpp

    #Tmp
    tmp/tmpcontroller.cpp
    tmp/tmpwidget.cpp
    tmp/tmpmodel.cpp
)

set(sources
    ${viewers_headers}
    ${viewers_sources}
)

source_group(TREE ${source_path} FILES ${sources})

add_library(UBCViewers STATIC)
target_sources(UBCViewers PRIVATE ${sources})

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
#find_package(nodes)

target_link_libraries(UBCViewers UBCCommon)

#target_compile_definitions(UBCViewers
#  PUBLIC
#    NODE_EDITOR_SHARED
#  PRIVATE
#    NODE_EDITOR_EXPORTS
#    #NODE_DEBUG_DRAWING
#    #QT_NO_KEYWORDS
#)



