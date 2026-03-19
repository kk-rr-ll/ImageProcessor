cmake_minimum_required(VERSION 3.16)
project(MyProject VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build example programs" ON)
option(INSTALL_EXAMPLES "Install example programs" OFF)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Debug build - with debug symbols and assertions")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Release build - with optimizations")
endif()

add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()