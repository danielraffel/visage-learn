cmake_minimum_required(VERSION 3.28)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(CMAKE_OSX_DEPLOYMENT_TARGET 10.15 CACHE STRING "Build for 10.14")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

project(visage-learn VERSION 0.0.1 LANGUAGES C CXX)

set(PRODUCT_NAME "Visage Learn")


option(USE_SANITIZER "Build and link with ASAN" FALSE)
option(COPY_AFTER_BUILD "Will copy after build" TRUE)
option(INCLUDE_ACCESSKIT "Include accesskit in build" FALSE)
include(cmake/compile-options.cmake)

include(libs/sst/sst-plugininfra/cmake/git-version-functions.cmake)
version_from_versionfile_or_git()
message(STATUS "DISPLAY_VERSION=${GIT_IMPLIED_DISPLAY_VERSION}; COMMIT_HASH=${GIT_COMMIT_HASH}; BRANCH=${GIT_BRANCH}")

include(cmake/CmakeRC.cmake)
file(GLOB_RECURSE PATCHES  "fonts/*.ttf")
cmrc_add_resource_library(${PROJECT_NAME}-fonts NAMESPACE resource_fonts ${PATCHES})

add_subdirectory(libs)

add_library(${PROJECT_NAME}-impl
        src/clap/visage-learn-entry-impl.cpp
        src/clap/visage-learn-clap.cpp

        src/ui/visage-learn-editor.cpp
        src/ui/fonts.cpp)
target_link_libraries(${PROJECT_NAME}-impl
        PRIVATE
        visage ${PROJECT_NAME}-fonts
        clap-helpers

        sst-plugininfra
        sst-plugininfra::filesystem
        sst-plugininfra::tinyxml
        sst-plugininfra::strnatcmp
        sst-plugininfra::patchbase
        sst-plugininfra::version_information

)
target_link_libraries(${PROJECT_NAME}-impl PUBLIC clap)
target_include_directories(${PROJECT_NAME}-impl PRIVATE src)
target_compile_definitions(${PROJECT_NAME}-impl PRIVATE PRODUCT_NAME="${PRODUCT_NAME}")
if (${INCLUDE_ACCESSKIT})
        target_link_libraries(${PROJECT_NAME}-impl PRIVATE accesskit)
        target_compile_definitions(${PROJECT_NAME}-impl PRIVATE HAS_ACCESSKIT=1)
else()
        target_compile_definitions(${PROJECT_NAME}-impl PRIVATE HAS_ACCESSKIT=0)
endif()


make_clapfirst_plugins(
        TARGET_NAME ${PROJECT_NAME}
        IMPL_TARGET ${PROJECT_NAME}-impl

        OUTPUT_NAME "${PRODUCT_NAME}"

        ENTRY_SOURCE src/clap/visage-learn-entry.cpp

        BUNDLE_IDENTIFER "org.baconpaul.visage-learn"
        BUNDLE_VERSION ${PROJECT_VERSION}

        COPY_AFTER_BUILD ${COPY_AFTER_BUILD}

        PLUGIN_FORMATS CLAP # VST3 AUV2

        ASSET_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME}_assets

        # You can add a target-per-standalone you want. Syntax here is
        #   target-postfix output-name clap-id
        # This allows you to make multiple standalones from a multi-plugin clap
        STANDALONE_CONFIGURATIONS
        standalone "${PRODUCT_NAME}" "org.baconpaul.visage-learn"
)

