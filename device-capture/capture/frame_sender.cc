#include "capture/frame_sender.h"
#include "protocol/leap.pb.h"

#include "Leap.h"
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>

namespace fleap = jp::co::atware::fiveoone::leap;

namespace leapcapture {

FrameSender::FrameSender(UdpClient &client) : client_(client) {}

fleap::Vector *convert(Leap::Vector vec) {
  auto r = std::make_unique<fleap::Vector>();
  r->set_x(vec.x);
  r->set_y(vec.y);
  r->set_z(vec.z);
  return r.release();
}

fleap::Hand *create(const Leap::Hand &hand) {
  auto h = std::make_unique<fleap::Hand>();
  h->set_id(hand.id());
  h->set_valid(true);

  auto fingers = hand.fingers();
  for (auto finger_it = fingers.begin(); finger_it != fingers.end();
       ++finger_it) {
    auto &finger = *finger_it;
    auto f = h->add_fingers();
    f->set_id(finger.id());
    f->set_type(static_cast<fleap::Finger::Type>(finger.type()));
    f->set_length(finger.length());
    f->set_width(finger.width());

    for (auto bi = 0; bi < 4; ++bi) {
      auto bone_type = static_cast<Leap::Bone::Type>(bi);
      auto b = f->add_bones();
      b->set_type(static_cast<fleap::Bone::Type>(bi));

      auto bone = finger.bone(bone_type);
      b->set_allocated_prev_joint(convert(std::move(bone.prevJoint())));
      b->set_allocated_next_joint(convert(std::move(bone.nextJoint())));
    }
  }
  return h.release();
}

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

  fleap::Frame f;
  f.set_id(frame.id());
  f.set_timestamp(frame.timestamp());
  const Leap::HandList hands = frame.hands();
  for (Leap::HandList::const_iterator it = hands.begin(); it != hands.end();
       ++it) {
    const Leap::Hand &hand = *it;
    if (hand.isLeft()) {
      f.set_allocated_left_hand(create(hand));
    } else {
      f.set_allocated_right_hand(create(hand));
    }
  }
  auto serialized = f.SerializeAsString();

  std::cout << frame.id()
            << " "
            // << frame.timestamp()
            << std::setw(4)
            << 1000 * 1000 / (frame.timestamp() - prev.timestamp())
            << " "
            // << frame.gesture(Leap::Gesture::TYPE_SWIPE).toString()
            << " " << serialized.size() << std::endl;
  client_.send(serialized);
}

} // namespace leapcapture
