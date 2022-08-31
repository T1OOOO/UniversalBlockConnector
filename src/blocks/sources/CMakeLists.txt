project(UBCSources)

add_library(UBCSources STATIC
    #Sender
    datasender/datasendercontroller.h
    datasender/datasendercontroller.cpp
    datasender/datasenderwidget.h
    datasender/datasenderwidget.cpp
    datasender/datasendermodel.h
    datasender/datasendermodel.cpp)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(nodes)

target_link_libraries(UBCSources UBCCommon Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets nodes)

#target_compile_definitions(UBCSources
#  PUBLIC
#    NODE_EDITOR_SHARED
#  PRIVATE
#    NODE_EDITOR_EXPORTS
#    #NODE_DEBUG_DRAWING
#    #QT_NO_KEYWORDS
#)

