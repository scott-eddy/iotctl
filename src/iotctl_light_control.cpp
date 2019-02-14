#include <iotctl_light_control.hpp>

namespace iotctl {
LightControl::LightControl(QObject *parent) : QObject (parent){
}


int LightControl::GetBrightness() {
  return brightness_;
}


void LightControl::SetBrightness(int value) {
  brightness_ = value;
  emit BrightnessChanged();
}

#include "moc_iotctl_light_control.cpp"
} // iotctl
