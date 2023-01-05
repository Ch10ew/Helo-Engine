cmake_minimum_required(VERSION 3.0.0)
project(HeloEngine VERSION 0.1.0)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Options
set(SFML_STATIC_LIBRARIES FALSE CACHE BOOL "TRUE to statically link SFML, FALSE to dynamically link SFML.")

# Setup for SFML build type (static/dynamic)
if(${SFML_STATIC_LIBRARIES})
    set(BUILD_SHARED_LIBS FALSE)
else()
    set(BUILD_SHARED_LIBS TRUE)
endif()

# Get SFML library from GitHub
include(ExternalProject)
ExternalProject_Add(sfml
    PREFIX "${CMAKE_BINARY_DIR}/lib"
    GIT_REPOSITORY "https://github.com/SFML/SFML.git"
    GIT_TAG "2.5.x"
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/sfml -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
)

# Prevent build for SFML on all targets build
set_target_properties(sfml PROPERTIES EXCLUDE_FROM_ALL TRUE)



# Get ImGUI library from GitHub
include(ExternalProject)
ExternalProject_Add(imgui-external
    PREFIX "${CMAKE_BINARY_DIR}/lib"
    GIT_REPOSITORY "https://github.com/ocornut/imgui.git"
    GIT_TAG "5c8041b4d7f62d343cc16333ca2ca9f49ae5488d"
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/lib/imgui"
    DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/lib/imgui"
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    CONFIGURE_COMMAND ""
)

add_library(imgui INTERFACE)



# Get ImGui-SFML library from GitHub
include(ExternalProject)
ExternalProject_Add(imgui-sfml
    PREFIX "${CMAKE_BINARY_DIR}/lib"
    GIT_REPOSITORY "https://github.com/eliasdaler/imgui-sfml.git"
    GIT_TAG "a80d9547832c57a149cda452ed9456def5bb6328"
    CMAKE_ARGS -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_INSTALL_PREFIX=${CMAKE_BINARY_DIR}/lib/imgui-sfml -DIMGUI_DIR=${CMAKE_BINARY_DIR}/lib/imgui -DSFML_DIR=${CMAKE_BINARY_DIR}/lib/src/sfml-build -DBUILD_SHARED_LIBS=${BUILD_SHARED_LIBS}
)

# Prevent build for ImGUI-SFML on all targets build
set_target_properties(imgui-sfml PROPERTIES EXCLUDE_FROM_ALL TRUE)



# Get debug_assert library from GitHub
include(ExternalProject)
ExternalProject_Add(debug_assert-external
        URL https://raw.githubusercontent.com/foonathan/debug_assert/master/debug_assert.hpp
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/lib/debug_assert"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/lib/debug_assert"
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        CONFIGURE_COMMAND ""
        DOWNLOAD_NO_EXTRACT TRUE
        DOWNLOAD_NAME "debug_assert.hpp"
)

add_library(debug_assert INTERFACE)



# Get aixlog library from GitHub
include(ExternalProject)
ExternalProject_Add(aixlog-external
        URL https://raw.githubusercontent.com/badaix/aixlog/master/include/aixlog.hpp
        SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/lib/aixlog"
        DOWNLOAD_DIR "${CMAKE_CURRENT_BINARY_DIR}/lib/aixlog"
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        CONFIGURE_COMMAND ""
        DOWNLOAD_NO_EXTRACT TRUE
        DOWNLOAD_NAME "aixlog.hpp"
)

add_library(aixlog INTERFACE)



# Define ${CMAKE_INSTALL_...} variables
include(GNUInstallDirs)



# Specify where third-party libraries are located
link_directories(${CMAKE_BINARY_DIR}/lib/sfml/${CMAKE_INSTALL_LIBDIR})
include_directories(${CMAKE_BINARY_DIR}/lib/sfml/${CMAKE_INSTALL_INCLUDEDIR})
link_directories(${CMAKE_BINARY_DIR}/lib/imgui/${CMAKE_INSTALL_LIBDIR})
include_directories(${CMAKE_BINARY_DIR}/lib/imgui/${CMAKE_INSTALL_INCLUDEDIR})
link_directories(${CMAKE_BINARY_DIR}/lib/imgui-sfml/${CMAKE_INSTALL_LIBDIR})
include_directories(${CMAKE_BINARY_DIR}/lib/imgui-sfml/${CMAKE_INSTALL_INCLUDEDIR})
link_directories(${CMAKE_BINARY_DIR}/lib/aixlog/${CMAKE_INSTALL_LIBDIR})
include_directories(${CMAKE_BINARY_DIR}/lib/aixlog/${CMAKE_INSTALL_INCLUDEDIR})

# This is required for SFML
find_package(OpenGL REQUIRED)

# This is CURRENTLY OPTIONAL
find_package(Threads REQUIRED)



# Set up ImGUI library
add_dependencies(imgui imgui-external)
target_include_directories(imgui SYSTEM INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/lib/imgui)

# Set up debug_assert library
add_dependencies(debug_assert debug_assert-external)
target_include_directories(debug_assert SYSTEM INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/lib/debug_assert)

# Set up aixlog library
add_dependencies(aixlog aixlog-external)
target_include_directories(aixlog SYSTEM INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/lib/aixlog)



# Include header directory
include_directories("./src/Engine/Public")
include_directories("./src/Game/Public")

# Create main target
file(GLOB_RECURSE sources src/*)
add_executable(Game ${sources})



if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(${SFML_STATIC_LIBRARIES})
        target_link_libraries(Game aixlog debug_assert imgui sfml-audio-s-d sfml-graphics-s-d sfml-window-s-d sfml-network-s-d sfml-system-s-d opengl32 winmm gdi32 opengl32 freetype openal32 flac vorbisenc vorbisfile vorbis ogg ws2_32 Threads::Threads libImGui-SFML_d)
    else()
        target_link_libraries(Game aixlog debug_assert imgui sfml-audio-d sfml-graphics-d sfml-window-d sfml-network-d sfml-system-d Threads::Threads libImGui-SFML_d)
    endif()
elseif(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
    if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        target_link_options(Game PRIVATE -mwindows)
    endif()
    if(${SFML_STATIC_LIBRARIES})
        target_link_libraries(Game aixlog debug_assert imgui sfml-audio-s sfml-graphics-s sfml-window-s sfml-network-s sfml-system-s opengl32 winmm gdi32 opengl32 freetype openal32 flac vorbisenc vorbisfile vorbis ogg ws2_32 Threads::Threads libImGui-SFML)
    else()
        target_link_libraries(Game aixlog debug_assert imgui sfml-audio sfml-graphics sfml-window sfml-network sfml-system Threads::Threads libImGui-SFML)
    endif()
endif()



# Copy over data folder
file(COPY data/ DESTINATION data)



# Make sure third-party libraries are built before executable
add_dependencies(Game sfml)
add_dependencies(imgui-sfml sfml)
add_dependencies(imgui-sfml imgui)
add_dependencies(Game imgui-sfml)
set_target_properties(Game PROPERTIES EXCLUDE_FROM_ALL TRUE)



# Add define for SFML if static (required by SFML)
if(${SFML_STATIC_LIBRARIES})
    add_compile_definitions(SFML_STATIC)
endif()



# Move SFML dlls
if(NOT ${SFML_STATIC_LIBRARIES})
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/openal32.dll"
                ${CMAKE_BINARY_DIR})
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-audio-d-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-graphics-d-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-network-d-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-system-d-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-window-d-2.dll"
                ${CMAKE_BINARY_DIR})
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-audio-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-graphics-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-network-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-system-2.dll"
                ${CMAKE_BINARY_DIR})
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/sfml/bin/sfml-window-2.dll"
                ${CMAKE_BINARY_DIR})
    endif()
endif()

# Move ImGUI-SFML dlls
if(NOT ${SFML_STATIC_LIBRARIES})
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${CMAKE_BINARY_DIR}/lib/imgui-sfml/bin/libImGui-SFML_d.dll"
                ${CMAKE_BINARY_DIR})
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_custom_command(TARGET Game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_BINARY_DIR}/lib/imgui-sfml/bin/libImGui-SFML.dll"
                ${CMAKE_BINARY_DIR})
    endif()
endif()
