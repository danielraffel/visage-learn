
add_subdirectory(clap-libs/clap EXCLUDE_FROM_ALL)
add_subdirectory(clap-libs/clap-helpers EXCLUDE_FROM_ALL)
add_subdirectory(fmt EXCLUDE_FROM_ALL)

add_library(simde INTERFACE)
target_include_directories(simde INTERFACE simde)

if (${INCLUDE_ACCESSKIT})
    message(STATUS "Downloading AccessKit")
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
endif()


add_subdirectory(sst/sst-basic-blocks)

set(SST_PLUGININFRA_PROVIDE_TINYXML ON CACHE BOOL "yesxml")
set(SST_PLUGININFRA_PROVIDE_PATCHBASE ON CACHE BOOL "patchbase pls")
add_subdirectory(sst/sst-plugininfra)

set(CLAP_WRAPPER_DOWNLOAD_DEPENDENCIES TRUE CACHE BOOL "Get em")
set(CLAP_WRAPPER_DONT_ADD_TARGETS TRUE CACHE BOOL "I'll targetize")
set(CLAP_WRAPPER_BUILD_AUV2 TRUE CACHE BOOL "It's only logical")
if (APPLE)
    # BaconPaul has jack kinda installed
    set(RTAUDIO_API_JACK FALSE CACHE BOOL "Not on apple")
endif()

add_subdirectory(clap-libs/clap-wrapper)

add_subdirectory(Visage)
