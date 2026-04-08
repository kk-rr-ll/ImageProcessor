if(NOT TARGET ImageProcessor)
    message(FATAL_ERROR "ImageProcessor target not found. Build src first.")
endif()

function(add_example EXAMPLE_NAME SOURCE_FILE)
    add_executable(${EXAMPLE_NAME} ${SOURCE_FILE})
    
    target_link_libraries(${EXAMPLE_NAME}
        PRIVATE
            ImageProcessor 
    )
    
    target_include_directories(${EXAMPLE_NAME}
        PRIVATE
            ${CMAKE_SOURCE_DIR}/include
            ${CMAKE_SOURCE_DIR}/src
    )
    
    target_include_directories(${EXAMPLE_NAME}
        PRIVATE
            ${EXTERNAL_INCLUDE_DIR}
    )
    
    set_target_properties(${EXAMPLE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    )
    
    target_link_libraries(${EXAMPLE_NAME}
        PRIVATE
            JPEG::JPEG
            PNG::PNG
            ZLIB::ZLIB
    )
    
    if(WIN32)
        target_link_libraries(${EXAMPLE_NAME}
            PRIVATE
                ws2_32
                shlwapi
        )
    endif()
    
    set_target_properties(${EXAMPLE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/examples"
        RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/examples"
    )
    
    set(TEST_DATA_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test_data)
    
    add_test(NAME ${EXAMPLE_NAME} COMMAND ${EXAMPLE_NAME})
    
    set_tests_properties(${EXAMPLE_NAME} PROPERTIES
        ENVIRONMENT "TEST_DATA_DIR=${TEST_DATA_DIR}"
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    )

    message(STATUS "Example ${EXAMPLE_NAME} configured with TEST_DATA_DIR=${TEST_DATA_DIR}")
endfunction()

add_example(bmprebyhe bmpResamplingByHeight.cpp)