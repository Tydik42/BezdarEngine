cmake_minimum_required(VERSION 3.10)
project("BezdarEngie")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/Engine/*.cpp")
add_executable (${PROJECT_NAME} main.cpp ${SOURCES})



include_directories(${CMAKE_SOURCE_DIR}/Engine)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/Engine)

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic)