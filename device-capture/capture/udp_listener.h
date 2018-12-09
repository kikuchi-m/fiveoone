#ifndef LEAPCAPTURE_UDP_LISTENER_H
#define LEAPCAPTURE_UDP_LISTENER_H

// #include "capture/export.h"
#include "Leap.h"

namespace leapcapture {

class UdpListener : public Leap::Listener {
public:
  void onInit(const Leap::Controller &) override;
  void onConnect(const Leap::Controller &) override;
  void onDisconnect(const Leap::Controller &) override;
  void onExit(const Leap::Controller &) override;
  void onFrame(const Leap::Controller &) override;
};

} // namespace leapcapture

#endif // LEAPCAPTURE_UDP_LISTENER_H
