#include <iotctl_http_client.hpp>
#include <iostream>

namespace iotctl {


HttpClient::HttpClient(QObject* parent) : QObject(parent) {

}

void HttpClient::SetUrl(const std::string& unencoded_query) {
    QString qt_url = QString::fromStdString(unencoded_query);
    active_url_ = QUrl(qt_url);
}

void HttpClient::BlockUntilGetComplete() {
  /* Create the QEventLoop */
   QEventLoop pause;
  /* connect the QHttp.requestFinished() Signal to the QEventLoop.quit() Slot */
  connect(this, &iotctl::HttpClient::HttpGetComplete, &pause, &QEventLoop::quit);
  /* Execute the QEventLoop - it will quit when the above finished due to the connect() */
   pause.exec();
  disconnect(this, &iotctl::HttpClient::HttpGetComplete, &pause, &QEventLoop::quit);
}

void HttpClient::StartGetFromActiveUrl() {
    ongoing_transaction_ = TransactionType::GET;
    transfer_complete_ = false;
    request_aborted_ = false;

    reply_ = net_access_man_.get(QNetworkRequest(active_url_));
    connect(reply_, &QNetworkReply::finished, this, &iotctl::HttpClient::HttpFinished);
    connect(reply_, &QIODevice::readyRead, this, &iotctl::HttpClient::HttpReadyRead);
}

void HttpClient::HttpFinished() {
    transfer_complete_ = true;
    if (request_aborted_) {
        std::cerr << "Request aborted" << std::endl;
        reply_->deleteLater();
        reply_ = nullptr;
        return;
    }

    if (reply_->error()) {
        std::cerr << "Request Failed" << std::endl;
        reply_->deleteLater();
        reply_ = nullptr;
        return;
    } else {
        data_available_ = true;
    }

    switch (ongoing_transaction_) {
      case TransactionType::GET:
        emit HttpGetComplete(size_received_data_);
        break;
    default:
        std::cerr << "ERROR, unkonwn transaction type";

    }
    ongoing_transaction_ = TransactionType::NONE;

}
void HttpClient::HttpReadyRead() {
    size_received_data_ += reply_->size();
    std::cout << "Reply!" << std::endl;
    std::cout << reply_->readAll().constData() << std::endl;
}


#include "moc_iotctl_http_client.cpp"
} // namespace iotctl
