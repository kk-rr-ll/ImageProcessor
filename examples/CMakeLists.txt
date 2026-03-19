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
    
    set_target_properties(${EXAMPLE_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/examples"
    )
    
    set_target_properties(${EXAMPLE_NAME} PROPERTIES
        DESCRIPTION "Example: ${EXAMPLE_NAME}"
    )
endfunction()

# examples
#add_example(examp examp.cpp)