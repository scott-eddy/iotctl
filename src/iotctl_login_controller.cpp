#include "iotctl_login_controller.h"
#include <QDebug>

namespace iotctl {

LoginController::LoginController(QObject *parent) : QObject (parent){

}

void LoginController::loginRequested(const QString& user, const QString& password) {
    qDebug() << "User: " << user;
    qDebug() << "Password: " << password;

}

#include "moc_iotctl_login_controller.cpp"
} // iotctl
