#include "udp-sample/sample.pb.h"

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>
#include <string>

using boost::asio::ip::udp;

class UdpClient {
public:
  UdpClient(boost::asio::io_context &io_context, std::string host = "127.0.0.1", short port = 22043)
      :
          address_(boost::asio::ip::make_address(host)),
          target_endpoint_(address_, port),
          socket_(io_context, udp::endpoint(udp::v4(), 0)) {
  }

  void send(const std::string &data) {
    socket_.send_to(boost::asio::buffer(data), target_endpoint_);
  }
  // enum { max_length = 1024 };

private:
  boost::asio::ip::address address_;
  udp::endpoint target_endpoint_;
  udp::socket socket_;
};

int main(int argc, char** argv) {
  std::string in;
  int32_t i = 0;

  try {
    boost::asio::io_context io_context;
    UdpClient client(io_context);
    while (true) {
      std::getline(std::cin, in);
      sample::Greeting g;
      g.set_id(i++);
      g.set_greetingmessage(in);
      client.send(g.SerializeAsString());
    }
  } catch (std::exception &e) {
    std::cout << "exception " << e.what() << std::endl;
  }
  return 0;
}
