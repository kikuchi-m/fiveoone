#include "capture/frame_sender.h"

#include "Leap.h"
#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

#include <iostream>

int main(int argc, char **argv) {
  try {
    boost::asio::io_context io_context;
    leapcapture::UdpClient client(io_context);
    leapcapture::FrameSender sender(client);

    Leap::Controller controller;
    controller.addListener(sender);
    controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
    controller.enableGesture(Leap::Gesture::TYPE_SWIPE);

    std::cout << "Press Q and Enter to exit " << std::endl;
    while (true) {
      char in;
      std::cin >> in;
      if (in == 'q') {
        break;
      }
    }

    controller.removeListener(sender);

  } catch (std::exception &e) {
    std::cout << "exception " << e.what() << std::endl;
  }

  return 0;
}
