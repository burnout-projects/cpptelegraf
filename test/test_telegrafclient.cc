#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <telegrafclient.h> // includes clientbase.h

class MockTelegrafClient : public IClientBase {
public:
  MOCK_METHOD4(metric, void(const std::string &measurement_name,
                            const std::unordered_map<std::string, std::string> &values,
                            const std::unordered_map<std::string, std::string> &tags,
                            const std::string &timestamp));
  MOCK_METHOD1(send, ssize_t(const std::string &data));
};

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

TEST(ClientTest, TestTwo) {
  MockTelegrafClient client;
  std::string testData = "testdata";
  EXPECT_CALL(client, send(testData));
  client.send(testData);
}
