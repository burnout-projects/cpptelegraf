#include <sys/socket.h>
#include <telegrafclient.h>
#include <unistd.h>

TelegrafClient::TelegrafClient(
    const std::string &host, int port,
    const std::unordered_map<std::string, std::string> &tags)
    : ClientBase(host, port, tags) {
  // Creating the socket immediately should be safe because it's UDP
  socket_ = socket(AF_INET, SOCK_DGRAM, 0);
}

TelegrafClient::~TelegrafClient() { close(socket_); }

ssize_t TelegrafClient::send(const std::string &data) {
  try {
    const auto len = data.length();
    const auto *const buffer = data.c_str();

    // Initialise server address
    std::memset(&server_address_, 0, sizeof(server_address_));
    server_address_.sin_family = AF_INET;
    server_address_.sin_port = htons(port_);
    if (inet_pton(AF_INET, host_.c_str(), &server_address_.sin_addr) <= 0) {
      // throw error
    }

    ssize_t ret_bytes;
    ret_bytes = sendto(socket_, buffer, len, 0,
           reinterpret_cast<const sockaddr *>(&server_address_),
           sizeof(server_address_));
    return ret_bytes;
  }
  catch (...)
  {
    // Socket errors should fail silently so they don't affect anything else
  }
}
