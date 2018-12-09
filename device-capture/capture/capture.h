#ifndef LEAPCAPTURE_CAPTURE_H
#define LEAPCAPTURE_CAPTURE_H

#include "Leap.h"

namespace leapcapture {

class Capture {
public
  Capture();
  virtual void start();
  virtual void stop();

private
  Leap::Controller controller;
}

} // namespace leapcapture

#endif // LEAPCAPTURE_CAPTURE_H
