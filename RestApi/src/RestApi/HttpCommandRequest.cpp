/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <RestApi/HttpCommandRequest.h>
#include <RestApi/CommandBase.h>

#include <QtCore/QDebug>

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

namespace GGS {
  namespace RestApi {

    HttpCommandRequest::HttpCommandRequest(QObject *parent) 
      : RequestBase(parent)
      , _networkManager(new QNetworkAccessManager(this))
    {
      connect(this->_networkManager, &QNetworkAccessManager::sslErrors,
        this, &HttpCommandRequest::sslErrors);
    }

    HttpCommandRequest::~HttpCommandRequest()
    {
    }

    void HttpCommandRequest::execute(const QUrl &request)
    {
      QString response;
      this->_requestString = request.toString();
      if (this->_cache && this->_cache->tryGet(this->_requestString, response)) {
          if (response.size()) {
            emit this->finish(CommandBase::NoError, response);
            return;
          }
      }

      //http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.2.1
      QNetworkReply *reply;
      if (this->_requestString.length() < 2048) {
        reply = this->_networkManager->get(QNetworkRequest(request));
      } else {
        QNetworkRequest postRequest(request);
        postRequest.setHeader(QNetworkRequest::ContentTypeHeader, QLatin1String("application/x-www-form-urlencoded"));
        reply = this->_networkManager->post(postRequest, request.query(QUrl::FullyEncoded).toUtf8());
      }

      connect(reply, &QNetworkReply::finished, this, &HttpCommandRequest::requestFinish);
    }

    void HttpCommandRequest::requestFinish()
    {
      QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
      reply->deleteLater();

      QString response = QString::fromUtf8(reply->readAll());
      QNetworkReply::NetworkError error = reply->error();

      if (this->_debugLogEnabled) {
        qDebug()
          << "Request  " << this->_requestString << "\n"
          << "NetworkError" << static_cast<quint32>(error)
          << "Response " << response << "\n";
      }

      CommandBase::CommandResults result;

      if (response.size() && error == QNetworkReply::NoError) {
        result = CommandBase::NoError;
      } else {
        WARNING_LOG << error;
        result = CommandBase::NetworkError;
      }

      emit this->finish(result, response);
    }

    void HttpCommandRequest::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
    {
      Q_FOREACH(QSslError error, errors) {
        WARNING_LOG << error;
      }

      reply->ignoreSslErrors();
    }
  }
}