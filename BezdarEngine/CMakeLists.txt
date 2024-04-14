cmake_minimum_required(VERSION 3.10)
project("BezdarEngie")

file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/Engine/*.cpp")
add_executable (${PROJECT_NAME} main.cpp ${SOURCES})


file(GLOB_RECURSE HEADER_FILES "${CMAKE_SOURCE_DIR}/Engine/*.h" "${CMAKE_SOURCE_DIR}/Engine/*.hpp")
foreach(FILE ${HEADER_FILES})
    get_filename_component(DIR ${FILE} DIRECTORY)
    list(APPEND HEADER_DIRS ${DIR})
endforeach()
list(REMOVE_DUPLICATES HEADER_DIRS)
include_directories(${HEADER_DIRS})

target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIRS})

if (CMAKE_VERSION VERSION_GREATER 3.12)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
endif()

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -pedantic)