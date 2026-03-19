include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/unit
)

function(add_unit_test TEST_NAME TEST_SOURCES)
    add_executable(${TEST_NAME} ${TEST_SOURCES})
    
    target_link_libraries(${TEST_NAME}
        PRIVATE
            ImageProcessor 
    )
    
    target_include_directories(${TEST_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/unit
    )
    
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    
    # Для более детального вывода
    set_tests_properties(${TEST_NAME} PROPERTIES
        ENVIRONMENT "TEST_DATA_DIR=${CMAKE_SOURCE_DIR}/test_data"
    )
endfunction()

# тесты для каждого модуля
# add_unit_test(test unit/test.cpp)