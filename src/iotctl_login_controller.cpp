#include "iotctl_login_controller.h"

namespace iotctl {

LoginController::LoginController(QObject *parent) : QObject (parent){

}

void LoginController::LoginRequested(const QString& user, const QString& password) {

}

#include "moc_iotctl_login_controller.cpp"
} // iotctl
