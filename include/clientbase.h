#include <string>
#include <unordered_map>
#include <arpa/inet.h>
#include <cstring>
#include <memory>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// Define the interface class
class IClientBase {
public:
  virtual ~IClientBase() {}

  virtual ssize_t metric(const std::string &measurement_name,
                      const std::unordered_map<std::string, std::string> &values,
                      const std::unordered_map<std::string, std::string> &tags = {},
                      const std::string &timestamp = "") = 0;

  virtual ssize_t send(const std::string &data) = 0;
};

// Modify the ClientBase class to implement the interface
class ClientBase : public IClientBase {
public:
  ClientBase(const std::string &host = "localhost", int port = 8094,
             const std::unordered_map<std::string, std::string> &tags = {});

  ssize_t metric(const std::string &measurement_name,
              const std::unordered_map<std::string, std::string> &values,
              const std::unordered_map<std::string, std::string> &tags = {},
              const std::string &timestamp = "");

  virtual ssize_t send(const std::string &data) override = 0;

protected:
  std::string host_;
  int port_;
  std::unordered_map<std::string, std::string> tags_;
};
