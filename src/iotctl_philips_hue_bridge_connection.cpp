#include <iotctl_philips_hue_bridge_connection.hpp>

namespace iotctl{
// Required in compilation unit
constexpr char PhilipsHueBridgeConnection::kHueBridgeLocationUrl[];


PhilipsHueBridgeConnection::PhilipsHueBridgeConnection() {
  client_.SetUrl(kHueBridgeLocationUrl);
  client_.StartGetFromActiveUrl();
  //client_.BlockUntilGetComplete();
}
}
