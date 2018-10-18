#include <RestApi/Request/HttpCommandRequest.h>

#include <RestApi/CacheInterface.h>

#include <RestApi/Command/CommandBase.h>
#include <RestApi/Command/RestApiCommandBase.h>

#include <QtCore/QDebug>
#include <QtCore/QUrlQuery>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

using P1::RestApi::Command::CommandBase;
using P1::RestApi::Command::RestApiCommandBase;

namespace P1 {
  namespace RestApi {
    namespace Request {

      HttpCommandRequest::HttpCommandRequest(QObject *parent)
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

      HttpCommandRequest::~HttpCommandRequest()
      {
      }

      void HttpCommandRequest::internalExecute()
      {
        RestApiCommandBase *cmd = qobject_cast<RestApiCommandBase*>(this->_command);
        QUrl url(cmd->apiUrl());
        QString path = QString("/api/%1/%2").arg(cmd->version(), cmd->method());
        url.setPath(path);

        QUrlQuery query;
        QMapIterator<QString, QString> it(cmd->commandParameters());
        while (it.hasNext()) {
          it.next();
          query.addQueryItem(QUrl::toPercentEncoding(it.key()), QUrl::toPercentEncoding(it.value()));
        }

        QString tmpQuery = query.toString(QUrl::ComponentFormattingOption::FullyEncoded);
        QString tmpUrl = url.toString();

        QString response;
        
        this->_requestString = tmpUrl;

        if (!tmpQuery.isEmpty())
          this->_requestString = tmpUrl + '?' + tmpQuery;

        if (this->_cache && this->_cache->tryGet(this->_requestString, response)) {
          cmd->setStatusCode(200);
          cmd->setResponse(response.toUtf8());
          this->resultReceived();
          return;
        }

        // http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.2.1
        bool shouldUsePost = cmd->supportPostRequest()
          && (tmpUrl.length() + tmpQuery.length() + 1) > cmd->getRequestMaxLength();

        if (!shouldUsePost)
          url.setQuery(query);

        QNetworkRequest request(url);

        if (shouldUsePost)
          request.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("application/x-www-form-urlencoded"));

        if (cmd->isAuthRequire()) {
          request.setRawHeader(
            QByteArray("Authorization"),
            QString("Bearer %1").arg(cmd->credential().acccessTokent()).toLatin1());
        }

        QNetworkReply *reply;
        if (shouldUsePost)
          reply = this->_networkManager->post(request, query.toString(QUrl::FullyEncoded).toUtf8());
        else
          reply = this->_networkManager->get(request);

        QObject::connect(reply, &QNetworkReply::finished, this, &HttpCommandRequest::requestFinish);
      }

      void HttpCommandRequest::requestFinish()
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
          if (this->_cache && this->_command->isCacheable()) {
            this->_cache->put(this->_requestString, QString::fromUtf8(response), this->_command->cacheTime());
          }
        }

        if (this->_debugLogEnabled) {
          qDebug()
            << "Request  " << this->_requestString << "\n"
            << "NetworkError " << static_cast<quint32>(error) << " StatusCode " << statusCode << "\n"
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