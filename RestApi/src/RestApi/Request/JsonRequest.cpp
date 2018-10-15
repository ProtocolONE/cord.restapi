#include <RestApi/Request/JsonRequest.h>

#include <RestApi/Command/JsonCommand.h>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

using P1::RestApi::Command::JsonCommand;
using P1::RestApi::Command::CommandBase;

namespace P1 {
  namespace RestApi {


    namespace Request {

      JsonRequest::JsonRequest(QObject *parent)
        : RequestBase(parent)
        , _networkManager(new QNetworkAccessManager(this))
      {
        QObject::connect(this->_networkManager, &QNetworkAccessManager::sslErrors, [](QNetworkReply *reply, const QList<QSslError> &errors) {
          Q_FOREACH(QSslError error, errors) {
            WARNING_LOG << error;
          }

          reply->ignoreSslErrors();
        });

      }

      void JsonRequest::internalExecute()
      {
        // INFO unsupported cache for now
        JsonCommand *cmd = qobject_cast<JsonCommand*>(this->_command);

        QUrl url(cmd->apiUrl());
        QString path = QString("/api/%1/%2").arg(cmd->version(), cmd->method());
        url.setPath(path);

        if (this->_debugLogEnabled) {
          qDebug() << "JsonRequest  " << url.toString();
        }

        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("application/json;charset=UTF-8"));
        QNetworkReply *reply;
        reply = this->_networkManager->post(request, cmd->postData());
        QObject::connect(reply, &QNetworkReply::finished, this, &JsonRequest::requestFinish);
      }

      void JsonRequest::requestFinish()
      {
        QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
        reply->deleteLater();

        QNetworkReply::NetworkError error = reply->error();
        QVariant status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
        int statusCode = 0;
        if (status.isValid())
          statusCode = status.toInt();

        QByteArray response;
        if (error == QNetworkReply::NoError && statusCode == 200) {
          response = reply->readAll();
          this->_command->setResponse(response);
        }

        if (this->_debugLogEnabled) {
          qDebug()
            << "JsonResponse NetworkError " << static_cast<quint32>(error) << " StatusCode " << statusCode << "\n"
            << "Response " << QString::fromUtf8(response) << "\n";
        }

        this->_command->setStatusCode(statusCode);

        if (!status.isValid())
          this->_command->setErrorCode(CommandBase::NetworkError);

        this->resultReceived();
      }

    }
  }
}
