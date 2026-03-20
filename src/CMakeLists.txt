file(GLOB SOURCES "*.cpp")
file(GLOB PRIVATE_HEADERS "*.h")

message(STATUS "Found source files: ${SOURCES}")

find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)

add_library(ImageProcessor STATIC ${SOURCES} ${PRIVATE_HEADERS})

target_include_directories(ImageProcessor 
    PUBLIC 
        ${CMAKE_SOURCE_DIR}/include
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(ImageProcessor 
    PUBLIC
        ${PNG_LIBRARIES}
        ${JPEG_LIBRARIES}
)