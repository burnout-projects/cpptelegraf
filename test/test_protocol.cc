#include <gtest/gtest.h>
#include <unordered_map>
#include <protocol.h>

struct ProtocolTestFixture : testing::Test {
  std::string measurement_ = "system_stats";
  std::unordered_map<std::string, std::string> values_ = {
      {"first", "80"}, {"second", "100.123"}, {"third", "true"}};
  std::unordered_map<std::string, std::string> tags_ = {
      {"fourth", "80"}, {"fifth", "100"}, {"sixth", "true"}};
  std::string timestamp_ = "12345678";
  Line line_ = Line{measurement_, values_, tags_, timestamp_};

  ProtocolTestFixture() {}

  ~ProtocolTestFixture() {}
};

TEST_F(ProtocolTestFixture, TestGetOutputMeasurement) {
  std::string expected = "system_stats";
  std::string actual = line_.get_output_measurement();

  ASSERT_EQ(expected, actual);
}

TEST_F(ProtocolTestFixture, TestGetOutputValues) {
  std::string expected = "third=true,second=100.123,first=80";
  std::string actual = line_.get_output_values();

  ASSERT_EQ(expected, actual);
}

TEST_F(ProtocolTestFixture, TestGetOutputTags) {
  std::string expected = "sixth=true,fifth=100,fourth=80";
  std::string actual = line_.get_output_tags();

  ASSERT_EQ(expected, actual);
}

TEST_F(ProtocolTestFixture, TestGetOutputTimeStamp) {
  std::string expected = " 12345678";
  std::string actual = line_.get_output_timestamp();

  ASSERT_EQ(expected, actual);
}

TEST_F(ProtocolTestFixture, TestToLineProtocol) {
  std::string expected = "system_stats,sixth=true,fifth=100,fourth=80 "
                         "third=true,second=100.123,first=80 12345678";
  std::string actual = line_.to_line_protocol();

  ASSERT_EQ(expected, actual);
}
