project(UBCViewers)

add_library(UBCViewers STATIC
    #Viewer
    dataviewer/dataviewercontroller.h
    dataviewer/dataviewercontroller.cpp
    dataviewer/dataviewerwidget.h
    dataviewer/dataviewerwidget.cpp
    dataviewer/dataviewermodel.h
    dataviewer/dataviewermodel.cpp)

#find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core Widgets)
#find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
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



