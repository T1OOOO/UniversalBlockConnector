project(UBCInterfaces)

set(source_path ${UBCInterfaces_SOURCE_DIR})

set(interfaces_headers
    #Udp
    udp/udpcontroller.h
    udp/udpwidget.h
    udp/udpdatamodel.h

    #Tcp server
    tcpserver/tcpservercontroller.h
    tcpserver/tcpserverwidget.h
    tcpserver/tcpserverdatamodel.h

    #Tcp server multi
    tcpservermulti/tcpservermulticontroller.h
    tcpservermulti/sockettabledelegate.h
    tcpservermulti/sockettablemodel.h
    tcpservermulti/tcpservermultiwidget.h
    tcpservermulti/tcpservermultidatamodel.h

    #Tcp client
    tcpclient/tcpclientcontroller.h
    tcpclient/tcpclientwidget.h
    tcpclient/tcpclientdatamodel.h

    #Serial
    serial/serialcontroller.h
    serial/serialwidget.h
    serial/serialdatamodel.h)

set(interfaces_sources
    #Udp
    udp/udpcontroller.cpp
    udp/udpwidget.cpp
    udp/udpdatamodel.cpp

    #Tcp server
    tcpserver/tcpservercontroller.cpp
    tcpserver/tcpserverwidget.cpp
    tcpserver/tcpserverdatamodel.cpp

    #Tcp server multi
    tcpservermulti/tcpservermulticontroller.cpp
    tcpservermulti/sockettabledelegate.cpp
    tcpservermulti/sockettablemodel.cpp
    tcpservermulti/tcpservermultiwidget.cpp
    tcpservermulti/tcpservermultidatamodel.cpp

    #Tcp client
    tcpclient/tcpclientcontroller.cpp
    tcpclient/tcpclientwidget.cpp
    tcpclient/tcpclientdatamodel.cpp

    #Serial
    serial/serialcontroller.cpp
    serial/serialwidget.cpp
    serial/serialdatamodel.cpp)

set(sources
    ${interfaces_headers}
    ${interfaces_sources}
)

source_group(TREE ${source_path} FILES ${sources})

add_library(UBCInterfaces STATIC)
target_sources(UBCInterfaces PRIVATE ${sources})

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core Widgets Network SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network SerialPort)
#find_package(NodeEditor)

target_link_libraries(UBCInterfaces UBCCommon Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Network Qt${QT_VERSION_MAJOR}::SerialPort nodes log4qt)

#target_compile_definitions(UBCSources
#  PUBLIC
#    NODE_EDITOR_SHARED
#  PRIVATE
#    NODE_EDITOR_EXPORTS
#    #NODE_DEBUG_DRAWING
#    #QT_NO_KEYWORDS
#)

