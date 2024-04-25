cmake_minimum_required(VERSION 3.20)
project(BezdarEngie)
add_executable (${PROJECT_NAME} main.cpp)

# Vcpkg
set(CMAKE_TOOLCHAIN_FILE "Vendor/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")

find_package(spdlog CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog_header_only)
target_compile_definitions(${PROJECT_NAME} PUBLIC SPDLOG_HEADER_ONLY)

find_package(fmt CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE fmt::fmt-header-only)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME}
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
        )


# DirectX12
find_library(D3DCOMPILER_LIB d3dcompiler)
target_link_libraries(${PROJECT_NAME} PRIVATE ${D3DCOMPILER_LIB})

if(TARGET Microsoft::DirectX12-Agility)
    file(MAKE_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/D3D12")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_PROPERTY:Microsoft::DirectX12-Core,IMPORTED_LOCATION_RELEASE> $<TARGET_FILE_DIR:${PROJECT_NAME}>/D3D12
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_PROPERTY:Microsoft::DirectX12-Layers,IMPORTED_LOCATION_DEBUG> $<TARGET_FILE_DIR:${PROJECT_NAME}>/D3D12
            COMMAND_EXPAND_LISTS
            )
endif()

find_package(directx-headers CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE Microsoft::DirectX-Headers)


#imgui
set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/Vendor/imgui)
add_library(imgui
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        )
target_include_directories(imgui PUBLIC ${IMGUI_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE imgui)


# Include directories
include_directories(${CMAKE_SOURCE_DIR}/Engine)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Engine)


file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/Engine/*.cpp")
target_sources(${PROJECT_NAME} PRIVATE ${SOURCES})


# Set C++ standard
set(CMAKE_CXX_STANDARD 20)


# Set compiler options
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic)


# PCH
target_precompile_headers(${PROJECT_NAME} PRIVATE Engine/pch.h)