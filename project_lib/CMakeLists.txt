CMAKE_MINIMUM_REQUIRED(VERSION 4.0)

PROJECT(ProjectLib CXX)

set(LIBRARY off)

file(GLOB SOURCE_FILES
	src/*.cpp
)

if (LIBRARY)
	add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
else()
	add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif()
set_target_properties(${PROJECT_NAME} PROPERTIES
   CXX_STANDARD 11
   CXX_STANDARD_REQUIRED ON
)
target_include_directories(${PROJECT_NAME} PRIVATE include/)

