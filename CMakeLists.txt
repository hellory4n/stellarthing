cmake_minimum_required(VERSION 3.24...3.30)
project(stellarthing)

include(FetchContent)

# haha
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/windows")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/windows/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/windows/lib")
    set(CMAKE_EXE_LINKER_FLAGS "-static")
elseif(UNIX AND NOT WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/linux")
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/linux/lib")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/linux/lib")
endif()

# Dependencies
set(RAYLIB_VERSION 5.5)

FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS
)

FetchContent_MakeAvailable(raylib)

include_directories(
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/src
)

file(GLOB_RECURSE PROJECT_SOURCES
    "${PROJECT_SOURCE_DIR}/src/*.h"
    "${PROJECT_SOURCE_DIR}/src/*.hpp"
    "${PROJECT_SOURCE_DIR}/src/*.cpp"
    "${PROJECT_SOURCE_DIR}/src/*.c"
    "${PROJECT_SOURCE_DIR}/lib/*.h"
    "${PROJECT_SOURCE_DIR}/lib/*.hpp"
    "${PROJECT_SOURCE_DIR}/lib/*.cpp"
    "${PROJECT_SOURCE_DIR}/lib/*.c"
)

# Our Project
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>)

#if ("${PLATFORM}" STREQUAL "Web")
#    add_custom_command(
#        TARGET ${PROJECT_NAME} PRE_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/../assets
#    )
#    #DEPENDS ${PROJECT_NAME}
#else()
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
    )
    #DEPENDS ${PROJECT_NAME}
#endif()

#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)

# we don't use those :)
# Web Configurations
#if ("${PLATFORM}" STREQUAL "Web")
#    # Tell Emscripten to build an example.html file.
#    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
#    target_link_options(${PROJECT_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC --preload-file resources)
#endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
#if (APPLE)
#    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
#    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
#    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
#endif()