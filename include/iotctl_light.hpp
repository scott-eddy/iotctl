#ifndef IOTCTL_LIGHT_HPP
#define IOTCTL_LIGHT_HPP

#include <stdint.h>

namespace iotctl {
class Light {
public:
  Light();

  /**
   * @brief Accessor
   * @return brightness_
   */
  uint8_t GetBrightness();

  /**
   * @brief Mutator
   * @param brightness, new value to set brightness_ to
   */
  void SetBrightness(uint8_t brightness);

private:
  uint8_t brightness_ = 0;
};

} // namespace ioctl

#endif // IOTCTL_LIGHT_HPP
