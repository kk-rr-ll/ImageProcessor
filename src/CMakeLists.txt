set(SOURCES
    image.cpp
    loaders/bmp_loader.cpp
    loaders/jpeg_loader.cpp
)

set(HEADERS
    loaders/bmp_loader.h
    loaders/jpeg_loader.h
    loaders/png_loader.h
)

message(STATUS "Found source files: ${SOURCES}")
message(STATUS "Found header files: ${HEADERS}")

add_library(ImageProcessor STATIC ${SOURCES} ${PRIVATE_HEADERS})

target_include_directories(ImageProcessor 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${JPEG_INCLUDE_DIRS}                 
        ${PNG_INCLUDE_DIRS}
)

target_link_libraries(ImageProcessor 
    PUBLIC
        ${PNG_LIBRARIES}
        ${JPEG_LIBRARIES}
)