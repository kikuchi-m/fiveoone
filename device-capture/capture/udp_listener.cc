#include "capture/udp_listener.h"

#include "Leap.h"
#include <iomanip>
#include <iostream>
#include <string>

namespace leapcapture {

void UdpListener::onInit(const Leap::Controller &) {
  std::cout << "initialized" << std::endl;
}

void UdpListener::onConnect(const Leap::Controller &controller) {
  std::cout << "connected" << std::endl;
  controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

void UdpListener::onDisconnect(const Leap::Controller &) {
  std::cout << "disconnected" << std::endl;
}

void UdpListener::onExit(const Leap::Controller &) {
  std::cout << "exit" << std::endl;
}

void UdpListener::onFrame(const Leap::Controller &controller) {
  const Leap::Frame frame = controller.frame();
  const Leap::Frame prev = controller.frame(1);
  std::cout
          << frame.id() << " "
          // << frame.timestamp()
          << std::setw(4) << 1000000 / (frame.timestamp() - prev.timestamp()) << " "
          << frame.gesture(Leap::Gesture::TYPE_SWIPE).toString()
          << std::endl;
}

} // namespace leapcapture
