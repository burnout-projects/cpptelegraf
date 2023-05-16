#include "gtest/gtest.h"

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}


// // main_test.cc
// #include <gtest/gtest.h>
// // #include <gmock/gmock.h>
// #include <protocol.h>
// #include <telegrafclient.h>
// #include <unordered_map>

// #include "test_protocol.h"
// #include "test_telegrafclient.h"

// // int main(int argc, char **argv) {
// //     ::testing::InitGoogleTest(&argc, argv);
// //     return RUN_ALL_TESTS();
// // }
