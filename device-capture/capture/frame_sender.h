#ifndef LEAPCAPTURE_FRAME_SENDER_H
#define LEAPCAPTURE_FRAME_SENDER_H

// #include "capture/export.h
#include "Leap.h"

namespace leapcapture {

class FrameSender : public Leap::Listener {
public:
  void onInit(const Leap::Controller &) override;
  void onConnect(const Leap::Controller &) override;
  void onDisconnect(const Leap::Controller &) override;
  void onExit(const Leap::Controller &) override;
  void onFrame(const Leap::Controller &) override;
};

} // namespace leapcapture

#endif // LEAPCAPTURE_FRAME_SENDER_H
