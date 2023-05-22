#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <unordered_map>
#include <telegrafclient.h> // includes clientbase.h

using ::testing::Return;
using ::testing::_;

class MockTelegrafClient : public IClientBase {
public:
  MOCK_METHOD4(metric, ssize_t(const std::string &measurement_name,
                            const std::unordered_map<std::string, std::string> &values,
                            const std::unordered_map<std::string, std::string> &tags,
                            const std::string &timestamp));
  MOCK_METHOD1(send, ssize_t(const std::string &data));
};

struct TelegrafClientTestFixture : testing::Test {
  std::unordered_map<std::string, std::string> tags_{{"region", "us-west"},
                                                    {"app", "example"}};
  std::unordered_map<std::string, std::string> values_{{"temperature", "22.1"},
                                                      {"humidity", "45"}};
  MockTelegrafClient client;
  
  TelegrafClientTestFixture() {}

  ~TelegrafClientTestFixture() {}
};

TEST_F(TelegrafClientTestFixture, TestOne) {
  MockTelegrafClient client;
  int expected = 78; // weather,app=example,region=us-west humidity="45",temperature="22.1" 1683219971
  EXPECT_CALL(client, metric(_, _, _, _)).WillOnce(Return(expected));
  ssize_t actual = client.metric("weather", values_, tags_, "1684263222");
  ASSERT_EQ(expected, actual);
}

TEST(ClientTest, TestTwo) {
  MockTelegrafClient client;
  std::string testData = "testdata";
  int expected = testData.length();
  EXPECT_CALL(client, send(testData)).WillOnce(Return(expected));
  ssize_t actual = client.send(testData);
  ASSERT_EQ(expected, actual);
}
