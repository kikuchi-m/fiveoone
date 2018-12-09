#include "capture/udp_listener.h"
#include "Leap.h"
#include <iostream>

int main(int argc, char** argv) {
  leapcapture::UdpListener listener;
  Leap::Controller controller;
  controller.addListener(listener);
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

  controller.removeListener(listener);

  return 0;
}
