#include <iotctl_light.hpp>

namespace iotctl {

uint8_t Light::GetBrightness() {
  return brightness_;
}

void Light::SetBrightness(uint8_t brightness) {
  brightness_ = brightness;
}

} // iotctl
