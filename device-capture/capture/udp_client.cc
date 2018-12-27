#include "capture/udp_client.h"

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>
#include <string>

using boost::asio::ip::udp;

namespace leapcapture {

UdpClient::UdpClient(boost::asio::io_context &io_context, std::string host,
                     short port)
    : address_(boost::asio::ip::make_address(host)),
      target_endpoint_(address_, port),
      socket_(io_context, udp::endpoint(udp::v4(), 0)) {}

void UdpClient::send(const std::string &data) {
  socket_.send_to(boost::asio::buffer(data), target_endpoint_);
}

} // namespace leapcapture
