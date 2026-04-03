set(SOURCES
    image.cpp
    loaders/bmp_loader.cpp
    loaders/jpeg_loader.cpp
    loaders/png_loader.cpp
    processors/resampling_processor.cpp
    processors/color_processor.cpp
)

set(HEADERS
    loaders/bmp_loader.h
    loaders/jpeg_loader.h
    loaders/png_loader.h
    processors/resampling_processor.h
    processors/color_processor.h
)

message(STATUS "Found source files: ${SOURCES}")
message(STATUS "Found header files: ${HEADERS}")

add_library(ImageProcessor STATIC ${SOURCES})

add_dependencies(ImageProcessor 
    libjpeg_project 
    libpng_project 
    zlib_project
)

target_include_directories(ImageProcessor 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
        ${EXTERNAL_INCLUDE_DIR}  
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ImageProcessor 
    PUBLIC
        JPEG::JPEG
        PNG::PNG
        ZLIB::ZLIB  
)