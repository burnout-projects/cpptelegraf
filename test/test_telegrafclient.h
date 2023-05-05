// #include <gtest/gtest.h>
// #include <unordered_map>
// #include <telegrafclient.h>

struct TelegrafClientTestFixture : testing::Test {
  std::unordered_map<std::string, std::string> tags_{{"region", "us-west"},
                                                    {"app", "example"}};
  TelegrafClient client_{"localhost", 8094, tags_};

  std::unordered_map<std::string, std::string> values_{{"temperature", "22.1"},
                                                      {"humidity", "45"}};

  TelegrafClientTestFixture() {}

  ~TelegrafClientTestFixture() {}
};

TEST_F(TelegrafClientTestFixture, TestOne) {
  client_.metric("weather", values_);
}

// int main(int argc, char **argv) {
//   testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
