project(UBCUtils)

set(source_path ${UBCUtils_SOURCE_DIR})

set(utils_headers loggermanager.h)
# buffer.h circularbuffer.h databuffer.h filebuffer.h filemanager.h
# protocolmanager.h stringutil.h

set(utils_sources loggermanager.cpp)
# buffer.cpp circularbuffer.cpp circularbuffersimple.cpp circularbuffersimple.h
# databuffer.cpp filebuffer.cpp filemanager.cpp protocolmanager.cpp
# stringutil.cpp

set(sources ${utils_headers} ${utils_sources})

source_group(TREE ${source_path} FILES ${sources})

add_library(UBCUtils STATIC)
target_sources(UBCUtils PRIVATE ${sources})

find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
# find_package(Log4Qt)

target_link_libraries(UBCUtils Qt${QT_VERSION_MAJOR}::Core log4qt)
