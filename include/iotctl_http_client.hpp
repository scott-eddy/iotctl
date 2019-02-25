#ifndef IOTCTL_HTTP_CLIENT_H
#define IOTCTL_HTTP_CLIENT_H

#include <QtNetwork>
#include <QObject>

namespace iotctl {

class HttpClient : public QObject {
   Q_OBJECT

public:

    explicit HttpClient(QObject* parent=nullptr);

    virtual ~HttpClient() = default;

    void SetUrl(const std::string& unencoded_url);

    /**
     * @brief Initiates an HTTP Get transfer on the network
     */
    void StartGetFromActiveUrl();

    /**
     * @brief Blocks until the current transfer is complete
     */
    void BlockUntilGetComplete();

signals:
    void HttpGetComplete(size_t size_received);

private slots:

    /**
     * @brief Signaled from QT network manager when the HTTP request has completed
     */
    void HttpFinished();

    /**
     * @brief Signlaled from QT when an HTTP request has returned data that is ready to read
     */
    void HttpReadyRead();

private:

    /**
     * @brief Type of ongoing HTTP transaction
    */
    enum class TransactionType {
        NONE,
        GET,
        POST
    };

    /**
     * @brief type of ongoing http transaction
     */
    TransactionType ongoing_transaction_;

    /**
     * @brief Accessor to the actual network
     */
    QNetworkAccessManager net_access_man_;

    /**
     * @brief reply for the active query
     */
    QNetworkReply *reply_ = nullptr;

    /**
     * @brief What to pull off of the network
     */
    QUrl active_url_;

    /**
     * @brief Indicates that an submitted transfer has been complted
     */
    bool transfer_complete_ = false;

    /**
     * @brief flag indicating that the Http request has been aborted
     */
    bool request_aborted_ = false;

    /**
     * @brief data_available_
     */
    bool data_available_ = false;

    /**
     * @brief Storage for the last network transaction
     */
    QByteArray network_data_;

    size_t size_received_data_ = 0;
};

} // iotctl

#endif // IOTCTL_HTTP_CLIENT_H
