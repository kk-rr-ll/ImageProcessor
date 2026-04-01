set(SOURCES
    image.cpp
    loaders/bmp_loader.cpp
    loaders/jpeg_loader.cpp
    loaders/png_loader.cpp
)

set(HEADERS
    loaders/bmp_loader.h
    loaders/jpeg_loader.h
    loaders/png_loader.h
)

message(STATUS "Found source files: ${SOURCES}")
message(STATUS "Found header files: ${HEADERS}")

add_library(ImageProcessor STATIC ${SOURCES})

add_dependencies(ImageProcessor JPEG::JPEG PNG::PNG)

target_include_directories(ImageProcessor 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ImageProcessor 
    PUBLIC
        JPEG::JPEG
        PNG::PNG
)