#include <string>
#include <unordered_map>
#include <arpa/inet.h>
#include <cstring>
#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

class ClientBase {
public:
  ClientBase(const std::string &host = "localhost", int port = 8094,
             const std::unordered_map<std::string, std::string> &tags = {});


  void metric(const std::string &measurement_name,
              const std::unordered_map<std::string, std::string> &values,
              const std::unordered_map<std::string, std::string> &tags = {},
              const std::string &timestamp = "");

  virtual void send(const std::string &data) = 0;

protected:
  std::string host_;
  int port_;
  std::unordered_map<std::string, std::string> tags_;
};
