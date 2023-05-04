#include <string>
#include <sstream>
#include <unordered_map>

class Line
{
public:
  Line(const std::string& measurement, const std::unordered_map<std::string, std::string>& values,
       const std::unordered_map<std::string, std::string>& tags = {}, const std::string& timestamp = "");

  std::string get_output_measurement() const;

  std::string get_output_values() const;

  std::string get_output_tags() const;

  std::string get_output_timestamp() const;

  std::string to_line_protocol() const;

private:
  std::string measurement_;
  std::unordered_map<std::string, std::string> values_;
  std::unordered_map<std::string, std::string> tags_;
  std::string timestamp_;
};
