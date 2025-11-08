# Clang toolchain file with LLDB debugging support
# This file configures CMake to use Clang compiler with LLDB debugging flags

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

# Set C and C++ compilers
if(NOT DEFINED CMAKE_C_COMPILER)
    set(CMAKE_C_COMPILER "clang")
endif()

if(NOT DEFINED CMAKE_CXX_COMPILER)
    set(CMAKE_CXX_COMPILER "clang++")
endif()

# Set compiler IDs
set(CMAKE_C_COMPILER_ID "Clang")
set(CMAKE_CXX_COMPILER_ID "Clang")

# Enable ccache for faster compilation (optional, can be disabled via ENABLE_CCACHE=OFF)
if(NOT DEFINED ENABLE_CCACHE)
    set(ENABLE_CCACHE ON CACHE BOOL "Use ccache to speed up compilation")
endif()

if(ENABLE_CCACHE)
    find_program(CCACHE_PROGRAM ccache)
    if(CCACHE_PROGRAM)
        message(STATUS "Found ccache: ${CCACHE_PROGRAM}")
        set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
        set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
        # Optional: Set custom ccache directory
        # set(CCACHE_DIR "${CMAKE_BINARY_DIR}/.ccache" CACHE PATH "ccache directory")
    else()
        message(WARNING "ccache not found. Install ccache to speed up compilation.")
        message(WARNING "  On Ubuntu/Debian: sudo apt install ccache")
        message(WARNING "  On Fedora: sudo dnf install ccache")
    endif()
endif()

# Enable colored diagnostics
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Debug flags for LLDB
# -glldb: Generate debug information in LLDB format (Clang-specific)
# -gdwarf-5: Use DWARF version 5 debug format
# -gline-tables-only: Generate line tables only (faster compilation, less debug info)
# -gfull: Generate full debug information (default with -g)
# -fstandalone-debug: Generate debug information for all types
# -fno-omit-frame-pointer: Keep frame pointers (important for debugging)
# -fno-optimize-sibling-calls: Disable tail call optimization (better stack traces)
# -O0: Disable optimizations for better debugging experience
set(CMAKE_C_FLAGS_DEBUG "-glldb -gdwarf-5 -fstandalone-debug -fno-omit-frame-pointer -fno-optimize-sibling-calls -O0")
set(CMAKE_CXX_FLAGS_DEBUG "-glldb -gdwarf-5 -fstandalone-debug -fno-omit-frame-pointer -fno-optimize-sibling-calls -O0")

# Release flags
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# RelWithDebInfo flags (optimized but with debug info)
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -glldb -gdwarf-5 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -glldb -gdwarf-5 -DNDEBUG")

# MinSizeRel flags
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")

# Additional compiler flags
# -Wall: Enable all warnings
# -Wextra: Enable extra warnings
# -Wpedantic: Warn about non-standard code
# -Wno-unused-parameter: Don't warn about unused parameters (useful for callbacks)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")

# Linker flags for LLDB
# -glldb: Include debug information in LLDB format in linked binary
# -gdwarf-5: Use DWARF version 5 format
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -glldb -gdwarf-5")
set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -glldb -gdwarf-5")
set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS_DEBUG} -glldb -gdwarf-5")

# Enable address sanitizer in debug builds (optional, can be enabled via cache variable)
if(ENABLE_ASAN)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=address")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address")
endif()

# Enable undefined behavior sanitizer (optional)
if(ENABLE_UBSAN)
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=undefined")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=undefined")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=undefined")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=undefined")
endif()

# Print configuration
message(STATUS "Using Clang toolchain")
message(STATUS "  C Compiler: ${CMAKE_C_COMPILER}")
message(STATUS "  C++ Compiler: ${CMAKE_CXX_COMPILER}")
if(ENABLE_CCACHE AND CCACHE_PROGRAM)
    message(STATUS "  ccache: Enabled (${CCACHE_PROGRAM})")
else()
    message(STATUS "  ccache: Disabled")
endif()
message(STATUS "  Build Type: ${CMAKE_BUILD_TYPE}")
message(STATUS "  CXX Flags Debug: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "  CXX Flags Release: ${CMAKE_CXX_FLAGS_RELEASE}")

