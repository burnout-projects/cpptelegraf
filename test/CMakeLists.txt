find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/lib/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/lib/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
                    "${source_dir}/googlemock/include")


# Now let's include the test files
file(GLOB SRCS *.cc)

ADD_EXECUTABLE(telegraf_tests ${SRCS})

TARGET_LINK_LIBRARIES(telegraf_tests
  TelegrafLibrary
  libgtest
  libgmock
)

add_test(NAME    telegraf_tests
         COMMAND telegraf_tests)


##############################################################


# # Set the path to the directory containing FindGMock.cmake
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

# find_package(GTest REQUIRED)
# find_package(GMock REQUIRED)

# set(GTEST_LIBRARIES ${GTEST_LIBRARIES})
# set(GMOCK_LIBRARIES ${GMOCK_LIBRARIES})

# add_library(libgtest IMPORTED STATIC GLOBAL)
# add_library(libgmock IMPORTED STATIC GLOBAL)

# set_target_properties(libgmock PROPERTIES
#     "IMPORTED_LOCATION" GMOCK_LIBRARIES
#     "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
# )

# set_target_properties(libgtest PROPERTIES
#     "IMPORTED_LOCATION" GTEST_LIBRARIES
#     "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
# )

# # include(GoogleTest)

# include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/test ${GMOCK_INCLUDE_DIRS} /usr/include/gtest)

# add_executable(telegraf_tests
#   test_main.cc  
#   test_protocol.cc
#   test_telegrafclient.cc
# )

# TARGET_LINK_LIBRARIES(telegraf_tests
#   TelegrafLibrary
#   libgtest
#   libgmock
# )

# target_link_libraries(telegraf_tests
# PRIVATE
#   GTest::GTest
#   ${GMOCK_BOTH_LIBRARIES}
#   TelegrafLibrary
# )

# add_test(telegraf_gtests telegraf_tests)
# include(GoogleTest)
# gtest_discover_tests(telegraf_tests)