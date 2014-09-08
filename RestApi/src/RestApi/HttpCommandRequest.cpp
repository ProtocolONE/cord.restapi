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
      : RequestBase(parent),
        _networkManager(new QNetworkAccessManager(this))
    {
      connect(this->_networkManager, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)), 
        this, SLOT(sslErrors(QNetworkReply *, const QList<QSslError>&)));
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
            emit finish(CommandBase::NoError, response);
            return;
          }
      }

      //http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.2.1
      QNetworkReply *reply = (this->_requestString.length() < 2048)
        ? this->_networkManager->get(QNetworkRequest(request))
        : this->_networkManager->post(QNetworkRequest(request), request.query(QUrl::FullyEncoded).toUtf8());

      connect(reply, SIGNAL(finished()), this, SLOT(requestFinish()));
    }

    void HttpCommandRequest::requestFinish()
    {
      QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
      reply->deleteLater();

      QString response = QString::fromUtf8(reply->readAll());
      QNetworkReply::NetworkError error = reply->error();

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