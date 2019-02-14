#ifndef IOTCTL_LIGHT_CONTROL_HPP
#define IOTCTL_LIGHT_CONTROL_HPP

#include <QObject>

namespace iotctl {

/**
 * @brief Controller for lights that interfaces with QML views
*/
class LightControl : public QObject {
  Q_OBJECT
  Q_PROPERTY(int brightness READ GetBrightness WRITE SetBrightness NOTIFY BrightnessChanged)

public:
  explicit LightControl(QObject *parent=nullptr);

  /**
   * @brief virtual DTOR
   */
  virtual ~LightControl() = default;
  /**
   * @brief Accessor
   * @return brightness_
   */
  int GetBrightness();

  /**
   * @brief
   * @param value
   */
  void SetBrightness(int value);

signals:

  void BrightnessChanged();

private:

    int brightness_ = 0;

};

} // namespace iotctl
#endif // IOTCTL_LIGHT_CONTROL_HPP
