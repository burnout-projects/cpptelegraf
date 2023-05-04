#include <cassert>
#include <protocol.h>
#include "utils.cpp"

Line::Line(const std::string& measurement, const std::unordered_map<std::string, std::string>& values,
           const std::unordered_map<std::string, std::string>& tags, const std::string& timestamp)
{
  assert(!measurement.empty());
  assert(!values.empty());

  measurement_ = measurement;
  values_ = values;
  tags_ = tags;
  timestamp_ = timestamp;
}

std::string Line::get_output_measurement() const
{
  return format_string(measurement_);
}

std::string Line::get_output_values() const
{
  std::stringstream ss;
  if (values_.size() == 1)
  {
    const auto& it = values_.begin();
    ss << it->first << "=" << format_value(it->second);
  }
  else
  {
    for (auto it = values_.begin(); it != values_.end(); ++it)
    {
      if (it != values_.begin())
      {
        ss << ",";
      }
      ss << it->first << "=" << format_value(it->second);
    }
  }
  return ss.str();
}

std::string Line::get_output_tags() const
{
  std::stringstream ss;
  if (!tags_.empty())
  {
    for (auto it = tags_.begin(); it != tags_.end(); ++it)
    {
      if (it != tags_.begin())
      {
        ss << ",";
      }
      ss << it->first << "=" << format_string(it->second);
    }
  }
  return ss.str();
}

std::string Line::get_output_timestamp() const
{
  if (!timestamp_.empty())
  {
    return " " + timestamp_;
  }
  else
  {
    return "";
  }
}

std::string Line::to_line_protocol() const
{
  std::stringstream ss;
  ss << get_output_measurement() << "," << get_output_tags() << " " << get_output_values() << get_output_timestamp();
  return ss.str();
}
