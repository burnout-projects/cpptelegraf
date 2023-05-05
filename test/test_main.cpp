// main_test.cc
#include <gtest/gtest.h>
#include <protocol.h>
#include <telegrafclient.h>
#include <unordered_map>

#include "test_protocol.h"
#include "test_telegrafclient.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
