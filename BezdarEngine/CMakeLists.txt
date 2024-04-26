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
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES})


# DirectX12
# Find the Win10 SDK path.
if ("$ENV{WIN10_SDK_PATH}$ENV{WIN10_SDK_VERSION}" STREQUAL "" )
    get_filename_component(WIN10_SDK_PATH "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows Kits\\Installed Roots;KitsRoot10]" ABSOLUTE CACHE)
    if (CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION)
        set (WIN10_SDK_VERSION ${CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION})
    else()
        # CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION may not be defined if, for example,
        # the Ninja generator is used instead of Visual Studio. Attempt to retrieve the
        # most recent SDK version from the list of paths under "${WIN10_SDK_PATH}/Include/".
        file(GLOB sdk_dirs RELATIVE "${WIN10_SDK_PATH}/Include/" "${WIN10_SDK_PATH}/Include/10.*")
        if (sdk_dirs)
            list(POP_BACK sdk_dirs WIN10_SDK_VERSION)
        endif()
        unset(sdk_dirs)
    endif()
elseif(TRUE)
    set (WIN10_SDK_PATH $ENV{WIN10_SDK_PATH})
    set (WIN10_SDK_VERSION $ENV{WIN10_SDK_VERSION})
endif ("$ENV{WIN10_SDK_PATH}$ENV{WIN10_SDK_VERSION}" STREQUAL "" )

# WIN10_SDK_PATH will be something like C:\Program Files (x86)\Windows Kits\10
# WIN10_SDK_VERSION will be something like 10.0.14393 or 10.0.14393.0; we need the
# one that matches the directory name.

if (IS_DIRECTORY "${WIN10_SDK_PATH}/Include/${WIN10_SDK_VERSION}.0")
    set(WIN10_SDK_VERSION "${WIN10_SDK_VERSION}.0")
endif (IS_DIRECTORY "${WIN10_SDK_PATH}/Include/${WIN10_SDK_VERSION}.0")


# Find the d3d12 and dxgi include path, it will typically look something like this.
# C:\Program Files (x86)\Windows Kits\10\Include\10.0.10586.0\um\d3d12.h
# C:\Program Files (x86)\Windows Kits\10\Include\10.0.10586.0\shared\dxgi1_4.h
find_path(D3D12_INCLUDE_DIR    # Set variable D3D12_INCLUDE_DIR
        d3d12.h                # Find a path with d3d12.h
        HINTS "${WIN10_SDK_PATH}/Include/${WIN10_SDK_VERSION}/um"
        DOC "path to WIN10 SDK header files"
        HINTS
        )

find_path(DXGI_INCLUDE_DIR    # Set variable DXGI_INCLUDE_DIR
        dxgi1_4.h           # Find a path with dxgi1_4.h
        HINTS "${WIN10_SDK_PATH}/Include/${WIN10_SDK_VERSION}/shared"
        DOC "path to WIN10 SDK header files"
        HINTS
        )
set(D3D12_INCLUDE_DIRS ${D3D12_INCLUDE_DIR} ${DXGI_INCLUDE_DIR})

# List of D3D libraries
set(D3D12_LIBRARIES d3d12.lib dxgi.lib d3dcompiler.lib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${D3D12_LIBRARIES})


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
#target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic)



# PCH
target_precompile_headers(${PROJECT_NAME} PRIVATE Engine/pch.h)