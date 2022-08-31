project(UBCCommon)

add_library(UBCCommon STATIC
    ledwidget.h
    ledwidget.cpp
    bytearraydatawidget.h
    bytearraydatawidget.cpp
    bytearraydatacontroller.h
    bytearraydatacontroller.cpp
    bytearraydatamodel.h
    bytearraydatamodel.cpp
    bytearraydata.h
    bytearraydata.cpp)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
find_package(NodeEditor)
find_package(Log4Qt)

target_link_libraries(UBCCommon Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets nodes log4qt)

target_compile_definitions(UBCCommon
  PUBLIC
    NODE_EDITOR_SHARED
  PRIVATE
    NODE_EDITOR_EXPORTS
    #NODE_DEBUG_DRAWING
    #QT_NO_KEYWORDS
)
