cmake_minimum_required(VERSION 3.16)
project(ImageProcessor VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(ExternalProject)

set(EXTERNAL_INSTALL_DIR ${CMAKE_BINARY_DIR}/external_install)
set(EXTERNAL_INCLUDE_DIR ${EXTERNAL_INSTALL_DIR}/include)
set(EXTERNAL_LIB_DIR ${EXTERNAL_INSTALL_DIR}/lib)

ExternalProject_Add(zlib_project
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/zlib
    BINARY_DIR ${CMAKE_BINARY_DIR}/zlib-build
    INSTALL_DIR ${EXTERNAL_INSTALL_DIR}
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_DIR}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DBUILD_SHARED_LIBS=OFF
        -DZLIB_BUILD_EXAMPLES=OFF
    BUILD_ALWAYS OFF
)

ExternalProject_Add(libjpeg_project
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/libjpeg
    BINARY_DIR ${CMAKE_BINARY_DIR}/libjpeg-build
    INSTALL_DIR ${EXTERNAL_INSTALL_DIR}
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_DIR}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DENABLE_SHARED=OFF
        -DENABLE_STATIC=ON
        -DWITH_TURBOJPEG=OFF
    BUILD_ALWAYS OFF
)

ExternalProject_Add(libpng_project
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/lib/libpng
    BINARY_DIR ${CMAKE_BINARY_DIR}/libpng-build
    INSTALL_DIR ${EXTERNAL_INSTALL_DIR}
    CMAKE_ARGS
        -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_DIR}
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DPNG_SHARED=OFF
        -DPNG_STATIC=ON
        -DPNG_TESTS=OFF
        -DPNG_BUILD_ZLIB=OFF  # Используем внешний zlib
        -DZLIB_ROOT=${EXTERNAL_INSTALL_DIR}
    BUILD_ALWAYS OFF
    DEPENDS zlib_project libjpeg_project  
)

file(MAKE_DIRECTORY ${EXTERNAL_INCLUDE_DIR})
file(MAKE_DIRECTORY ${EXTERNAL_LIB_DIR})

add_library(ZLIB::ZLIB STATIC IMPORTED GLOBAL)
set_target_properties(ZLIB::ZLIB PROPERTIES
    IMPORTED_LOCATION ${EXTERNAL_LIB_DIR}/libz.a
    INTERFACE_INCLUDE_DIRECTORIES ${EXTERNAL_INCLUDE_DIR}
)
add_dependencies(ZLIB::ZLIB zlib_project)

add_library(JPEG::JPEG STATIC IMPORTED GLOBAL)
set_target_properties(JPEG::JPEG PROPERTIES
    IMPORTED_LOCATION ${EXTERNAL_LIB_DIR}/libjpeg.a
    INTERFACE_INCLUDE_DIRECTORIES ${EXTERNAL_INCLUDE_DIR}
)
add_dependencies(JPEG::JPEG libjpeg_project)

add_library(PNG::PNG STATIC IMPORTED GLOBAL)
set_target_properties(PNG::PNG PROPERTIES
    IMPORTED_LOCATION ${EXTERNAL_LIB_DIR}/libpng.a
    INTERFACE_INCLUDE_DIRECTORIES ${EXTERNAL_INCLUDE_DIR}
    INTERFACE_LINK_LIBRARIES ZLIB::ZLIB 
)
add_dependencies(PNG::PNG libpng_project)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build example programs" ON)

add_subdirectory(src)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()