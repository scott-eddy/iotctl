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

QColor LightControl::GetColor() {
  return color_;
}

void LightControl::SetColor(const QColor& color) {
  color_ = color;
  emit ColorChanged();
}

#include "moc_iotctl_light_control.cpp"
} // iotctl
