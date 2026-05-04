cmake_minimum_required(VERSION 3.10)
project(Pokemony_Pamietaja_O_Zarzadzaniu_Pamiecia LANGUAGES CXX)

set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR
        "Nie buduj projektu w katalogu źródłowym.\n"
        "Użyj:\n"
        "  mkdir build\n"
        "  cd build\n"
        "  cmake ..\n"
    )
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(SOURCE_DIR  "${PROJECT_SOURCE_DIR}/src")
include_directories(${INCLUDE_DIR})
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

add_executable(${PROJECT_NAME}
    Main.cpp
    ${SOURCES}
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror=return-type
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    PROJECTPATH="${PROJECT_SOURCE_DIR}"
)

if(ENABLE_ERROR_TEST)
    target_compile_definitions(${PROJECT_NAME} PRIVATE ENABLE_ERROR_TEST=1)
endif()

if(DEBUG_MODE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_MODE=1)
endif()

