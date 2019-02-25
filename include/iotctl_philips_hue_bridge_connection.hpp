#ifndef IOTCTL_PHILIPS_HUE_BRIDGE_CONNECTION_H
#define IOTCTL_PHILIPS_HUE_BRIDGE_CONNECTION_H

#include <iotctl_http_client.hpp>
#include <QString>
#include <QHostAddress>

namespace iotctl {

class PhilipsHueBridgeConnection : public QObject {
   Q_OBJECT

public:

    /**
     * @brief Gets the hue basic info by performing an HTTP
     *        Get on kHueBridgeLocationUrl and parsing
     *        the result into basic_info_
     */
    explicit PhilipsHueBridgeConnection(QObject* parent=nullptr);

    virtual ~PhilipsHueBridgeConnection() = default;

    struct BasicInfo {
        QString id;
        QHostAddress address;
    };

    BasicInfo GetDeviceInfo();

private slots:

    /**
     * @brief Nofification when HTTP get responses are complete
     */
    void BridgeGetResponseComplete(size_t size_received);

private:

    void ParseBasicInfo(const QString& info_result);

    /**
     * @brief Access to the network
     */
    HttpClient client_;

    BasicInfo bridge_info_;

    static constexpr char kHueBridgeLocationUrl[] = "https://discovery.meethue.com";
};

} // iotctl

#endif // IOTCTL_PHILIPS_HUE_BRIDGE_CONNECTION_H
