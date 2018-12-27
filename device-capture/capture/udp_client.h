#ifndef LEAPCAPTURE_UDP_CLIENT_H
#define LEAPCAPTURE_UDP_CLIENT_H

#include <boost/asio.hpp>

#include <string>

using boost::asio::ip::udp;

namespace leapcapture {

class UdpClient {
public:
  UdpClient(boost::asio::io_context &io_context, std::string host = "127.0.0.1",
            short port = 22043);

  void send(const std::string &data);

private:
  boost::asio::ip::address address_;
  udp::endpoint target_endpoint_;
  udp::socket socket_;
};

} // namespace leapcapture

#endif // LEAPCAPTURE_UDP_CLIENT_H
