cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

project(TelegrafLibrary VERSION 1.0.0 LANGUAGES CXX)

option(BUILD_TESTS "Build unit tests" OFF)

if (BUILD_TESTS)
    find_package(GTest REQUIRED)
endif()

set(__ipo_ok FALSE)
if (POLICY CMP0069)
    cmake_policy(SET CMP0069 NEW)

    include(CheckIPOSupported)
    check_ipo_supported(RESULT __ipo_ok OUTPUT __ipo_err LANGUAGES CXX)
    if (NOT __ipo_ok)
        message(STATUS "IPA ${__ipo_err}")
    endif()
endif()

# This project is intended only for GNU/LLVM compilers.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")

add_subdirectory(src)

if (BUILD_TESTS AND GTEST_FOUND)
    enable_testing()
    add_subdirectory(test)
endif()
