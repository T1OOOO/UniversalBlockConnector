project(UBCUtils)

add_library(UBCUtils STATIC
    loggermanager.h
    loggermanager.cpp
    buffer.cpp
    buffer.h
    circularbuffer.cpp
    circularbuffer.h
    circularbuffersimple.cpp
    circularbuffersimple.h
    databuffer.cpp
    databuffer.h
    filebuffer.cpp
    filebuffer.h
    filemanager.cpp
    filemanager.h
    protocolmanager.cpp
    protocolmanager.h
    stringutil.cpp
    stringutil.h)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Log4Qt)

target_link_libraries(UBCUtils Qt${QT_VERSION_MAJOR}::Core log4qt)



