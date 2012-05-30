/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <RestApi/GameNetCredential.h>
#include <RestApi/Auth/GenericAuth.h>

#include <QtCore/QDebug>
#include <QtCore/QUrl>
#include <QtCore/QCryptographicHash>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Auth {
      
      GenericAuth::GenericAuth() 
        : _methodType("generic"),
          _networkManager(new QNetworkAccessManager(this))
      {
        connect(this->_networkManager, SIGNAL(sslErrors(QNetworkReply*, const QList<QSslError>&)), 
          this, SLOT(sslErrors(QNetworkReply *, const QList<QSslError>&)));
      }

      GenericAuth::~GenericAuth()
      {
      }

      const QString& GenericAuth::type()
      {
        return this->_methodType;
      }

      void GenericAuth::setAuthUrl( const QString& authUrl )
      {
        this->_authUrl = authUrl;
      }

      void GenericAuth::setLogin( const QString& loginName )
      {
        this->_login = loginName;
      }

      void GenericAuth::setPassword( const QString& password )
      {
        this->_password = password;
      }

      void GenericAuth::login()
      {
        QString passHash(QCryptographicHash::hash(this->_password.toUtf8(), QCryptographicHash::Sha1).toHex());

        QUrl authRequest(this->_authUrl);
        authRequest.addQueryItem("login", this->_login);
        authRequest.addQueryItem("passhash", passHash);

        QNetworkReply *reply = this->_networkManager->get(QNetworkRequest(authRequest));
        connect(reply, SIGNAL(finished()), this, SLOT(requestFinish()));
      }

      void GenericAuth::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
      {
        Q_FOREACH(QSslError error, errors) {
          WARNING_LOG << error;
        }
        
        reply->ignoreSslErrors();
      }

      void GenericAuth::requestFinish()
      {
        QNetworkReply *reply = qobject_cast<QNetworkReply*>(QObject::sender());
        reply->deleteLater();

        QNetworkReply::NetworkError error = reply->error();
        
        if (QNetworkReply::NoError != reply->error()) { 
          emit this->authFailed(NetworkError);  
          return;
        }

        QDomDocument document;
        if (!document.setContent(reply->readAll())) {
          emit this->authFailed(NetworkError); 
          return;
        }

        QDomElement responseElement = document.documentElement();
        QDomElement errorElement = responseElement.firstChildElement("error");
        QDomElement errorMessage = errorElement.firstChildElement("message");
        QDomElement errorCode  = errorElement.firstChildElement("code");

        if (!errorMessage.isNull() || !errorCode.isNull()) {
          int genericErrorMessageCode = errorCode.text().toInt();   
          
          if (genericErrorMessageCode == 100 || genericErrorMessageCode == 110)
            emit this->authFailed(WrongLoginOrPassword); 
          else 
            emit this->authFailed(UnknownError);   
          
          return;
        }

        QDomElement authElement = responseElement.firstChildElement("auth");
        QDomElement userIdElement = authElement.firstChildElement("userId");

        if(userIdElement.isNull()) {
          emit this->authFailed(UnknownError);   
          return;
        }

        GameNetCredential credential;
        credential.setUserId(userIdElement.text());

        QDomElement appKeyElement = authElement.firstChildElement("appKey");
        if (appKeyElement.isNull()) {
          emit this->authFailed(UnknownError);   
          return;
        }

        credential.setAppKey(appKeyElement.text());

        QDomElement cookieElement = authElement.firstChildElement("cookie");
        if (cookieElement.isNull()) {
          emit this->authFailed(UnknownError);
          return;
        }

        credential.setCookie(QUrl::toPercentEncoding(cookieElement.text()));
        emit this->authResult(credential);
      }
    }
  }
}