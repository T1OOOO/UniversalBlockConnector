project(UBCModyfiers)

add_library(UBCModyfiers STATIC
    #Delay
    delay/delaycontroller.h
    delay/delaycontroller.cpp
    delay/delaywidget.h
    delay/delaywidget.cpp
    delay/delaydatamodel.h
    delay/delaydatamodel.cpp

    #Lost
    lost/lostcontroller.cpp
    lost/lostcontroller.h
    lost/lostdatamodel.cpp
    lost/lostdatamodel.h
    lost/lostwidget.cpp
    lost/lostwidget.h
)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(nodes)

target_link_libraries(UBCModyfiers UBCCommon Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets nodes log4qt)

#target_compile_definitions(UBCModyfiers
#  PUBLIC
#    NODE_EDITOR_SHARED
#  PRIVATE
#    NODE_EDITOR_EXPORTS
#    #NODE_DEBUG_DRAWING
#    #QT_NO_KEYWORDS
#)

