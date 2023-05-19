set(srcs
    test_main.cc
    test_protocol.cc
    test_telegrafclient.cc)

add_executable(utests ${srcs})
target_include_directories(utests
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(utests
    PRIVATE
        ${PROJECT_NAME}
        GTest::gtest
        GTest::gtest_main
        GTest::gmock
        GTest::gmock_main)
set_target_properties(utests
    PROPERTIES POSITION_INDEPENDENT_CODE ON)

if (NOT CMAKE_BUILD_TYPE STREQUAL "Debug" AND __ipo_ok)
    set_target_properties(utests
        PROPERTIES INTERPROCEDURAL_OPTIMIZATION ON)
endif()

add_test(utests utests)
