cmake_minimum_required(VERSION 3.16)
project(MyProject VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build example programs" ON)

find_package(JPEG REQUIRED)
find_package(PNG REQUIRED)

if(JPEG_FOUND)
    message(STATUS "JPEG found: ${JPEG_LIBRARIES}")
    message(STATUS "JPEG include: ${JPEG_INCLUDE_DIRS}")
endif()

if(PNG_FOUND)
    message(STATUS "PNG found: ${PNG_LIBRARIES}")
    message(STATUS "PNG include: ${PNG_INCLUDE_DIRS}")
endif()

add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()