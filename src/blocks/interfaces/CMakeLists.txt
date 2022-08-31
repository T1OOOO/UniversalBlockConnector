project(UBCInterfaces)

add_library(UBCInterfaces STATIC
    #Udp
    udp/udpcontroller.h
    udp/udpcontroller.cpp
    udp/udpwidget.h
    udp/udpwidget.cpp
    udp/udpdatamodel.h
    udp/udpdatamodel.cpp

    #Tcp server
    tcpserver/tcpservercontroller.h
    tcpserver/tcpservercontroller.cpp
    tcpserver/tcpserverwidget.h
    tcpserver/tcpserverwidget.cpp
    tcpserver/tcpserverdatamodel.h
    tcpserver/tcpserverdatamodel.cpp

    #Tcp server multi
    tcpservermulti/tcpservermulticontroller.h
    tcpservermulti/tcpservermulticontroller.cpp
    tcpservermulti/sockettabledelegate.h
    tcpservermulti/sockettabledelegate.cpp
    tcpservermulti/sockettablemodel.h
    tcpservermulti/sockettablemodel.cpp
    tcpservermulti/tcpservermultiwidget.h
    tcpservermulti/tcpservermultiwidget.cpp
    tcpservermulti/tcpservermultidatamodel.h
    tcpservermulti/tcpservermultidatamodel.cpp

    #Tcp client
    tcpclient/tcpclientcontroller.h
    tcpclient/tcpclientcontroller.cpp
    tcpclient/tcpclientwidget.h
    tcpclient/tcpclientwidget.cpp
    tcpclient/tcpclientdatamodel.h
    tcpclient/tcpclientdatamodel.cpp

    #Serial
    serial/serialcontroller.h
    serial/serialcontroller.cpp
    serial/serialwidget.h
    serial/serialwidget.cpp
    serial/serialdatamodel.h
    serial/serialdatamodel.cpp)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core Widgets Network SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Network SerialPort)
find_package(NodeEditor)

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

