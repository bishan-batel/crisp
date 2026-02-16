cmake_minimum_required(VERSION 3.16)

project(crisp)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories to just lib and bin instead of keeping subdirectory structure
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Force colored outputs by default
option (FORCE_COLORED_OUTPUT "Always produce ANSI-colored output (GNU/Clang only)." TRUE)
if (${FORCE_COLORED_OUTPUT})
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        add_compile_options (-fdiagnostics-color=always)
    elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options (-fcolor-diagnostics)
    endif ()
endif ()

# Dependencies

option(CPM_USE_LOCAL_PACKAGES "Should CPM look for local packages?" ON)

include(cmake/CPM.cmake)

CPMAddPackage(
        NAME fmt
        GITHUB_REPOSITORY "fmtlib/fmt"
        GIT_TAG "12.1.0"
        VERSION_MIN "9.0.0"
)

# find_package(fmt CONFIG REQUIRED)
# find_package(crab CONFIG REQUIRED)
CPMAddPackage("gh:bishan-batel/crab@2.3.1")

add_subdirectory(src)
