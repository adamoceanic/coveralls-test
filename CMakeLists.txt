cmake_minimum_required(VERSION 3.8)
project(coveralls-test)

# Set the Standard version.
include(CheckCXXCompilerFlag)

check_cxx_compiler_flag("-std=c++14" COMPILER_SUPPORTS_CXX14)
check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if (COMPILER_SUPPORTS_CXX14)
    add_definitions(-std=c++14)
elseif (COMPILER_SUPPORTS_CXX11)
    add_definitions(-std=c++11)
elseif (COMPILER_SUPPORTS_CXX0X)
    add_definitions(-std=c++0x)
else ()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif ()


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake-coveralls)

option(COVERALLS "Generate coveralls data" OFF)


if (COVERALLS)
    include(Coveralls)
    coveralls_turn_on_coverage()
endif()

if (COVERALLS)
    set(COVERAGE_SRCS C1.h C1.cpp C2.h C2.cpp main.cpp)

    # Create the coveralls target.
    coveralls_setup(
            "${COVERAGE_SRCS}" # The source files.
            ON)               # If we should upload.

endif()


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -pipe")
set(CMAKE_EXE_LINKER_FLAGS "-pthread")

set(GCC_COVERAGE_COMPILE_FLAGS "-g -O0 -coverage -fprofile-arcs -ftest-coverage")
set(GCC_COVERAGE_LINK_FLAGS "-coverage -lgcov")
# -lstdc++fs - for safe keeping (--enable-libstdcxx-filesystem-ts)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

add_subdirectory(test)

set(SOURCE_FILES main.cpp main.cpp C1.cpp C1.h C2.cpp C2.h)
add_executable(MyApp ${SOURCE_FILES})