cmake_minimum_required(VERSION 3.28)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE STRING "Build for 10.14")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(visage-learn VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)


include(FetchContent)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/_accesskit/ak.zip")
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/_accesskit)
        file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/_accesskit-bin)
        file(DOWNLOAD
                https://github.com/AccessKit/accesskit-c/releases/download/0.14.0/accesskit-c-0.14.0.zip
                ${CMAKE_BINARY_DIR}/_accesskit/ak.zip
                )
        execute_process(
                WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/_accesskit-bin
                COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_BINARY_DIR}/_accesskit/ak.zip
        )
endif()
set(ACCESSKIT_DIR ${CMAKE_BINARY_DIR}/_accesskit-bin/accesskit-c-0.14.0)
find_package(ACCESSKIT REQUIRED)

include(cmake/CmakeRC.cmake)
file(GLOB_RECURSE PATCHES  "fonts/*.ttf")
cmrc_add_resource_library(${PROJECT_NAME}-fonts NAMESPACE resource_fonts ${PATCHES})

add_subdirectory(libs/Visage)

add_executable(${PROJECT_NAME} src/main.cpp src/fonts.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE visage ${PROJECT_NAME}-fonts )
if (FALSE)
        target_link_libraries(${PROJECT_NAME} PRIVATE accesskit)
        target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_ACCESSKIT=1)
else()
        target_compile_definitions(${PROJECT_NAME} PRIVATE HAS_ACCESSKIT=0)
endif()
