#include <clientbase.h>
#include <protocol.h>

ClientBase::ClientBase(const std::string &host, int port,
                       const std::unordered_map<std::string, std::string> &tags)
    : host_(host), port_(port), tags_(tags) {}

void ClientBase::metric(
    const std::string &measurement_name,
    const std::unordered_map<std::string, std::string> &values,
    const std::unordered_map<std::string, std::string> &tags,
    const std::string &timestamp) {
  if (measurement_name.empty() || values.empty()) {
    // Don't try to send empty data
    return;
  }

  // Do a shallow merge of the metric tags and global tags
  std::unordered_map<std::string, std::string> all_tags(tags_);
  all_tags.insert(tags.begin(), tags.end());

  // Create a metric line from the input and then send it to socket
  Line line(measurement_name, values, all_tags, timestamp);
  send(line.to_line_protocol());
}
