project(UBCCommon)

set(source_path ${UBCCommon_SOURCE_DIR})

set(common_headers ledwidget.h bytearraydatawidget.h bytearraydatacontroller.h
                   bytearraydatamodel.h bytearraydata.h
)

set(common_sources
    ledwidget.cpp bytearraydatawidget.cpp bytearraydatacontroller.cpp
    bytearraydatamodel.cpp bytearraydata.cpp
)

set(sources ${common_headers} ${common_sources})

source_group(TREE ${source_path} FILES ${sources})

add_library(UBCCommon STATIC)
target_sources(UBCCommon PRIVATE ${sources})

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)
# find_package(NodeEditor) find_package(Log4Qt)

target_link_libraries(
    UBCCommon Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets nodes
    log4qt
)
