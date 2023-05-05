find_package(GTest REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/test)

add_executable(telegraf_tests
  test_main.cpp
)

target_link_libraries(telegraf_tests
PRIVATE
  GTest::GTest
  ${CMAKE_SOURCE_DIR}/libTelegrafLibrary.so
)

add_test(telegraf_gtests telegraf_tests)