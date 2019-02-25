#include <iotctl_philips_hue_bridge_connection.hpp>
#include <iostream>

namespace iotctl{
// Required in compilation unit
constexpr char PhilipsHueBridgeConnection::kHueBridgeLocationUrl[];


PhilipsHueBridgeConnection::PhilipsHueBridgeConnection(QObject* parent) : QObject(parent) {
  client_.SetUrl(kHueBridgeLocationUrl); 
  //connect(this, &iotctl::PhilipsHueBridgeConnection::BridgeGetResponseComplete, &client_, nullptr);
  connect(&client_, &iotctl::HttpClient::HttpGetComplete, this, &iotctl::PhilipsHueBridgeConnection::BridgeGetResponseComplete);
  client_.StartGetFromActiveUrl();
  client_.BlockUntilGetComplete();
}


PhilipsHueBridgeConnection::BasicInfo PhilipsHueBridgeConnection::GetDeviceInfo() {
    return bridge_info_;
}

void PhilipsHueBridgeConnection::ParseBasicInfo(const QString& info_result) {

}

void PhilipsHueBridgeConnection::BridgeGetResponseComplete(size_t size_received) {
    std::cout << "Read: " << size_received << " bytes!";
    disconnect(&client_, &iotctl::HttpClient::HttpGetComplete, this, &iotctl::PhilipsHueBridgeConnection::BridgeGetResponseComplete);
}

#include "moc_iotctl_philips_hue_bridge_connection.cpp"
} //iotctl
