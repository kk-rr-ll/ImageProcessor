cmake_policy(SET CMP0135 NEW)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_data)
file(MAKE_DIRECTORY ${TEST_DATA_DIR})

function(add_unit_test TEST_NAME TEST_SOURCES)
    add_executable(${TEST_NAME} ${TEST_SOURCES})
    
    target_link_libraries(${TEST_NAME}
        PRIVATE
            ImageProcessor
            GTest::gtest_main
            ${EXTERNAL_LIB_DIR}/libjpeg.a
            ${EXTERNAL_LIB_DIR}/libpng.a
            ${EXTERNAL_LIB_DIR}/libz.a 
            ${CMAKE_DL_LIBS}
    )
    
    target_include_directories(${TEST_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/src
            ${EXTERNAL_INCLUDE_DIR}
    )
    
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    
    set_tests_properties(${TEST_NAME} PROPERTIES
        ENVIRONMENT "TEST_DATA_DIR=${TEST_DATA_DIR}"
    )
    
    message(STATUS "Test ${TEST_NAME} configured with TEST_DATA_DIR=${TEST_DATA_DIR}")
endfunction()

add_unit_test(test_image test_image.cpp)