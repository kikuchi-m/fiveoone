#include "udp-sample/sample.pb.h"

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>

using boost::asio::ip::udp;

class UdpServer {
public:
  UdpServer(boost::asio::io_context &io_context, short port = 22043)
      : socket_(io_context, udp::endpoint(udp::v4(), port)) {
    doReceive();
  }

private:
  void doReceive() {
    socket_.async_receive_from(
        boost::asio::buffer(data_, max_length), sender_endpoint_,
        [&](boost::system::error_code ec, std::size_t bytes) {
          if (!ec) {
            msg.ParseFromArray(&data_, bytes);
            std::cout << "recived (" << bytes << "): " << msg.id() << " " << msg.greetingmessage() << std::endl;
          } else {
            std::cout << "error " << ec.value() << std::endl;
          }
          doReceive();
        });
  }

  udp::socket socket_;
  udp::endpoint sender_endpoint_;
  enum { max_length = 1024 };
  char data_[max_length];
  sample::Greeting msg;
};

int main(int argc, char** argv) {
  try {
    boost::asio::io_context io_context;
    UdpServer server(io_context);
    io_context.run();
  } catch (std::exception &e) {
    std::cout << "exception " << e.what() << std::endl;
  }
  return 0;
}
