#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iotctl_light_control.hpp>
#include <iotctl_login_controller.h>
#include <iotctl_filesystem_manager.h>

int main(int argc, char *argv[])
{

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // Initialize all filesystem management
    iotctl::FileSystemManger::GetInstance();

    qmlRegisterType<iotctl::LightControl>("iotctl.light_control", 1, 0, "LightControl");
    qmlRegisterType<iotctl::LoginController>("iotctl.login_controller", 1, 0, "LoginController");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
