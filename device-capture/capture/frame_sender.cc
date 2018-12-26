#include "capture/frame_sender.h"

#include "Leap.h"
#include <iomanip>
#include <iostream>
#include <string>

namespace leapcapture {

void FrameSender::onInit(const Leap::Controller &) {
  std::cout << "initialized" << std::endl;
}

void FrameSender::onConnect(const Leap::Controller &controller) {
  std::cout << "connected" << std::endl;
  controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
}

void FrameSender::onDisconnect(const Leap::Controller &) {
  std::cout << "disconnected" << std::endl;
}

void FrameSender::onExit(const Leap::Controller &) {
  std::cout << "exit" << std::endl;
}

void FrameSender::onFrame(const Leap::Controller &controller) {
  const Leap::Frame frame = controller.frame();
  const Leap::Frame prev = controller.frame(1);
  std::cout
          << frame.id() << " "
          // << frame.timestamp()
          << std::setw(4) << 1000 * 1000 / (frame.timestamp() - prev.timestamp()) << " "
          << frame.gesture(Leap::Gesture::TYPE_SWIPE).toString()
          << std::endl;
}

} // namespace leapcapture
