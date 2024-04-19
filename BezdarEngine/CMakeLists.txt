cmake_minimum_required(VERSION 3.10)
project(BezdarEngie)

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/Engine/*.cpp")
add_executable (${PROJECT_NAME} main.cpp)
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})


# Include directories
include_directories(${CMAKE_SOURCE_DIR}/Engine)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Engine)


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)


# Set compiler options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic)


# PCH
target_precompile_headers(${PROJECT_NAME} PRIVATE Engine/pch.h)


# Vcpkg
set(CMAKE_TOOLCHAIN_FILE "Vendor/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)
target_compile_definitions(${PROJECT_NAME} PUBLIC SPDLOG_HEADER_ONLY)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)

find_package(sdl2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2 SDL2::SDL2main)
