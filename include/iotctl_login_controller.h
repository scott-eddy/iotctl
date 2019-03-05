#ifndef IOTCTL_LOGIN_CONTROLLER_H
#define IOTCTL_LOGIN_CONTROLLER_H

#include <QObject>
#include <QString>

namespace iotctl {

/**
 * @brief class that interfaces with
*/
class LoginController : public QObject {
  Q_OBJECT

public:
  explicit LoginController(QObject *parent=nullptr);

  /**
   * @brief virtual DTOR
   */
  virtual ~LoginController() = default;

public slots:

    /**
     * @brief Nofification when a user/login combo has been entered by the user
     */
    void LoginRequested(const QString& user, const QString& password);
};

} // iotctl
#endif // IOTCTL_LOGIN_CONTROLLER_H
