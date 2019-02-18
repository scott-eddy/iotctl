#ifndef IOTCTL_PHILIPS_HUE_BRIDGE_CONNECTION_H
#define IOTCTL_PHILIPS_HUE_BRIDGE_CONNECTION_H

#include <iotctl_http_client.hpp>

namespace iotctl {

class PhilipsHueBridgeConnection {
public:
    PhilipsHueBridgeConnection();

    ~PhilipsHueBridgeConnection() = default;

    void GetDeviceInfo();

private:

    /**
     * @brief Access to the network
     */
    HttpClient client_;

    static constexpr char kHueBridgeLocationUrl[] = "https://discovery.meethue.com";
};

} // iotctl

#endif // IOTCTL_PHILIPS_HUE_BRIDGE_CONNECTION_H
