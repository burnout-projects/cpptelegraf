#include <clientbase.h>
#include <netinet/in.h>

class TelegrafClient : public ClientBase {
public:
  TelegrafClient(const std::string &host = "localhost", int port = 8094,
                 const std::unordered_map<std::string, std::string> &tags = {});

  ~TelegrafClient();

  ssize_t send(const std::string &data) override;

private:
  int socket_;
  sockaddr_in server_address_;
};
