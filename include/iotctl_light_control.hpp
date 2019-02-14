#ifndef IOTCTL_LIGHT_CONTROL_HPP
#define IOTCTL_LIGHT_CONTROL_HPP

#include <QObject>
#include <QColor>

namespace iotctl {

/**
 * @brief Controller for lights that interfaces with QML views
*/
class LightControl : public QObject {
  Q_OBJECT
  Q_PROPERTY(int brightness READ GetBrightness WRITE SetBrightness NOTIFY BrightnessChanged)
  Q_PROPERTY(QColor color READ GetColor WRITE SetColor NOTIFY ColorChanged)

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
   * @brief Accessor
   * @return color_
   */
  QColor GetColor();

  /**
   * @brief Mutator
   * @param color
   */
  void SetColor(const QColor& color);

  /**
   * @brief
   * @param value
   */
  void SetBrightness(int value);

signals:

  /**
   * @brief Emitted when the brightness of the light has actually changed
   *        TODO(escott) this would need to tie into the backend of
   *
   */
  void BrightnessChanged();

  /**
   * @brief emitted when the color of the light has actually changed
   */
  void ColorChanged();

private:

    int brightness_ = 0;

    QColor color_;

};

} // namespace iotctl
#endif // IOTCTL_LIGHT_CONTROL_HPP
