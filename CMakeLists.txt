cmake_minimum_required(VERSION 3.28)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE STRING "Build for 10.14")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(visage-learn VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)


include(cmake/CmakeRC.cmake)
file(GLOB_RECURSE PATCHES  "fonts/*.ttf")
cmrc_add_resource_library(${PROJECT_NAME}-fonts NAMESPACE resource_fonts ${PATCHES})

add_subdirectory(libs/Visage)

add_executable(${PROJECT_NAME} src/main.cpp src/fonts.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE visage ${PROJECT_NAME}-fonts)
