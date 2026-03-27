include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)
FetchContent_MakeAvailable(googletest)

# Функция для добавления юнит-теста
function(add_unit_test TEST_NAME TEST_SOURCES)
    add_executable(${TEST_NAME} ${TEST_SOURCES})
    
    target_link_libraries(${TEST_NAME}
        PRIVATE
            ImageProcessor
            GTest::gtest_main
    )
    
    target_include_directories(${TEST_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}
    )
    
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endfunction()


add_unit_test(test_image test_image.cpp)