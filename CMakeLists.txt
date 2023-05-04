cmake_minimum_required(VERSION 3.5)

project(TelegrafLibrary VERSION 1.0.0 LANGUAGES CXX)

# Specify the include directory
include_directories(include)


enable_testing()
add_subdirectory(test)

# Define the library target
add_library(TelegrafLibrary STATIC
    src/protocol.cpp
)

# Set public header files
set_target_properties(TelegrafLibrary PROPERTIES PUBLIC_HEADER
    include/protocol.h
)

# Define include directories
target_include_directories(TelegrafLibrary PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Set compiler options
target_compile_options(TelegrafLibrary PRIVATE -Wall -Wextra -pedantic)

# Set linker options
target_link_libraries(TelegrafLibrary PRIVATE
    # Add any required third-party libraries here
)

# Install rules
install(TARGETS TelegrafLibrary
    EXPORT TelegrafLibraryTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include
)

# Install CMake package configuration files
install(EXPORT TelegrafLibraryTargets
    FILE TelegrafLibraryTargets.cmake
    NAMESPACE TelegrafLibrary::
    DESTINATION lib/cmake/TelegrafLibrary
)

set(TelegrafLibrary_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the TelegrafLibraryConfig.cmake files")



# Generate CMake package configuration files
include(CMakePackageConfigHelpers)
configure_package_config_file(
    ${TelegrafLibrary_CMAKE_DIR}/TelegrafLibraryConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/TelegrafLibraryConfig.cmake
    INSTALL_DESTINATION lib/cmake/TelegrafLibrary
)

# Install CMake package configuration files
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/TelegrafLibraryConfig.cmake
    DESTINATION lib/cmake/TelegrafLibrary
)
