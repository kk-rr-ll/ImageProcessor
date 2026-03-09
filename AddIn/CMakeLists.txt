# Cmake script for project AddInNative
# autor: 1C

CMAKE_MINIMUM_REQUIRED(VERSION 4.0 FATAL_ERROR)

foreach(policy CMP0068)
  if(POLICY ${policy})
    cmake_policy(SET ${policy} NEW)
  endif()
endforeach()

PROJECT(AddInNative CXX)

IF(WIN32)
    ENABLE_LANGUAGE(RC)
ENDIF()
#----------------------------------------------------------------------------------------------------------------#
#--source files-------------------
SET(AddInNative_SRC 
    AddInNative.cpp
    AddInNative.h
    dllmain.cpp
    stdafx.cpp
    stdafx.h
    )
if (WIN32)
    LIST(APPEND AddInNative_SRC AddInNative.rc AddInNative.def)
endif()
#--source files end---------------
set(ADN_NAME ${PROJECT_NAME})
set(MECONPANY "MyCompany")
#----------------------------------------------------------------------------------------------------------------#
include_directories(${CMAKE_SOURCE_DIR}/include)

SET (CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${CMAKE_SOURCE_DIR})

if (UNIX)
    if (APPLE)
        ADD_DEFINITIONS(-D__APPLE__ )
    endif()
else()
    add_definitions(-DUNICODE -DWIN32 -D_USRDLL -D_CRT_SECURE_NO_WARNINGS -D_CRT_SECURE_NO_DEPRECATE -DADDINCPP_EXPORTS)
endif()
if(APPLE)
    set(BNDL ${PROJECT_NAME}Bndl)
    SET(Addn_MimeType "application/component-example-1" CACHE STRING "MIMEType for NPAPI project" )

    add_library(${BNDL} MODULE ${AddInNative_SRC})
    set_target_properties( ${BNDL} PROPERTIES
       POSITION_INDEPENDENT_CODE ON 
       CXX_STANDARD 11
       CXX_STANDARD_REQUIRED ON
   )
    target_include_directories(${BNDL} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
    
    set_target_properties(${BNDL} PROPERTIES BUNDLE TRUE)
    set_target_properties( ${BNDL} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
    SET(MACOSX_BUNDLE_INFO_STRING "${PROJECT_NAME}")

    SET(MACOSX_BUNDLE_COPYRIGHT "Copyright ${YEAR} ${MYCOMPANY}.")
    TARGET_LINK_LIBRARIES(${BNDL} "-framework CoreFoundation" iconv)
    set_target_properties(${BNDL} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/MacOSXBundleInfo.plist.in)
    
    #Safari pkg
    SET(PKG_NAME "AddInSafOSX")
    get_target_property(BUNDLE_NAME ${BNDL} OUTPUT_NAME)

    set(MIMETYPE "${Addn_MimeType}")
    file(COPY ${CMAKE_SOURCE_DIR}/lib/1CEAdnWebNPAPISafOSX.bundle DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in ${CMAKE_CURRENT_BINARY_DIR}/1CEAdnWebNPAPISafOSX.bundle/Contents/Info.plist)
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/1CEAdnWebNPAPISafOSX.bundle/Contents/PlugIns)
    
    #FIXME Get BUNDLE full name
    add_custom_command(TARGET ${BNDL} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_BINARY_DIR}/${BUNDLE_NAME}.bundle ${CMAKE_CURRENT_BINARY_DIR}/1CEAdnWebNPAPISafOSX.bundle/Contents/PlugIns/${BUNDLE_NAME}.bundle
        COMMENT "Copy ${BNDL}"
        MAIN_DEPENDENCY ${BNDL}
    )
    add_custom_target(saf_productbuild ALL DEPENDS ${BNDL}
        COMMAND productbuild --component ${CMAKE_CURRENT_BINARY_DIR}/1CEAdnWebNPAPISafOSX.bundle "/Library/Internet Plug-Ins/" ${CMAKE_CURRENT_BINARY_DIR}/${PKG_NAME}.pkg
        COMMENT "Create package for Safari"
        MAIN_DEPENDENCY ${BNDL}
    )
    #add_custom_target( saf_productsign ALL DEPENDS saf_productbuild
    #    COMMAND productsign --sign "Developer ID Installer: ${SIGNCERT}"  ${CMAKE_CURRENT_BINARY_DIR}/${PKG_NAME}.pkg ${PKG_OUTPUT_DIR}/${PKG_NAME}.pkg
    #    COMMENT "Signing package for Safari"
    #    MAIN_DEPENDENCY ${BNDL}
    #)
endif()

add_library(${PROJECT_NAME} SHARED ${AddInNative_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
if (APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE iconv)
endif()

if (WIN32)
    target_precompile_headers(${PROJECT_NAME} PUBLIC stdafx.h)
endif()

set_target_properties( ${PROJECT_NAME} PROPERTIES
       POSITION_INDEPENDENT_CODE ON 
       CXX_STANDARD 11
       CXX_STANDARD_REQUIRED ON
   )
IF (UNIX AND NOT APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-Wl,--no-undefined -Xlinker --version-script -Xlinker ${CMAKE_CURRENT_SOURCE_DIR}/version.script" )
ENDIF()
