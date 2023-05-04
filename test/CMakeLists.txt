find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(telegraf_tests test_protocol.cpp)

target_link_libraries(telegraf_tests
PRIVATE
  GTest::GTest
  ${CMAKE_SOURCE_DIR}/libTelegrafLibrary.a)

add_test(telegraf_gtests telegraf_tests)