#include <iotctl_philips_hue_bridge_connection.hpp>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    iotctl::HttpClient client;
    client.SetUrl("https://discovery.meethue.com");
    client.StartGetFromActiveUrl();
    //iotctl::PhilipsHueBridgeConnection();
    app.exec();
}
