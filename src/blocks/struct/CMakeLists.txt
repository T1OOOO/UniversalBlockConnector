project(UBCStructs)

set(source_path ${UBCStructs_SOURCE_DIR})

set(sources_headers
    # Viewer
    structviewer/structviewercontroller.h
    structviewer/structviewerwidget.h
    structviewer/structviewermodel.h
    structviewer/structviewerlistmodel.h
    # Graph viewer
    structgraphviewer/structgraphviewercontroller.h
    structgraphviewer/structgraphviewerwidget.h
    structgraphviewer/structgraphviewermodel.h
    structgraphviewer/structchart.h
    # Sender
    structsender/structsendercontroller.h
    structsender/structsenderwidget.h
    structsender/structsendermodel.h
    # structsender/structsenderlistmodel.h
    # Util
    utils/highlighter.h
)

set(sources_sources
    # Viewer
    structviewer/structviewercontroller.cpp
    structviewer/structviewerwidget.cpp
    structviewer/structviewermodel.cpp
    structviewer/structviewerlistmodel.cpp
    # Graph viewer
    structgraphviewer/structgraphviewercontroller.cpp
    structgraphviewer/structgraphviewerwidget.cpp
    structgraphviewer/structgraphviewermodel.cpp
    structgraphviewer/structchart.cpp
    # Sender
    structsender/structsendercontroller.cpp
    structsender/structsenderwidget.cpp
    structsender/structsendermodel.cpp
    # structsender/structsenderlistmodel.cpp
    # Util
    utils/highlighter.cpp
)

include(GNUInstallDirs)

set(jsonmodel_path ${CMAKE_SOURCE_DIR}/3rdparty/QJsonModel)

set(jsonmodel_sources ${jsonmodel_path}/qjsonmodel.h
                      ${jsonmodel_path}/qjsonmodel.cpp
)

set(sources ${sources_headers} ${sources_sources})

source_group(TREE ${source_path} FILES ${sources})
source_group(TREE ${jsonmodel_path} FILES ${jsonmodel_sources})

list(APPEND sources ${jsonmodel_sources})

add_library(UBCStructs STATIC)
target_sources(UBCStructs PRIVATE ${sources})

target_include_directories(
    UBCStructs PRIVATE ${CMAKE_SOURCE_DIR}/src/blocks ${jsonmodel_path}
)

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Charts)
# find_package(nodes)

target_link_libraries(
    UBCStructs
    PRIVATE UBCCommon Qt${QT_VERSION_MAJOR}::Core
            Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Charts nodes
            qbinarizer::qbinarizer
)

# target_compile_definitions(UBCStructs PUBLIC NODE_EDITOR_SHARED PRIVATE
# NODE_EDITOR_EXPORTS #NODE_DEBUG_DRAWING #QT_NO_KEYWORDS )
