/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "Auth/GenericAuth.h"

namespace GGS {
  namespace RestApi {
    namespace Auth {

      GenericAuth::GenericAuth(void)
      {
        this->_methodType = "generic";
        // UNDONE: Хотя... если считать этот класс в единственном экземпляре, то вызвать можно и тут.
        curl_global_init(CURL_GLOBAL_ALL);
        this->_resultCallback = 0;
      }

      GenericAuth::~GenericAuth(void)
      {
      }

      void GenericAuth::login()
      {
       QtConcurrent::run(this, &GenericAuth::loginSync);
      }

      void GenericAuth::setResultCallback( GameNetAuthResultInterface *result )
      {
        this->_resultCallback = result;
      }

      QString GenericAuth::passwordHash( const QString& password )
      {
        return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Algorithm::Sha1).toHex());
      }

      void GenericAuth::loginSync()
      {
        // Пока что синхронный метод, возможно стоит вынести в поток
        HttpRequest http;
        HttpRequestInterface::ResultCodes result;

        QString query("login=");
        query.append(QUrl::toPercentEncoding(this->_login));
        query.append("&passhash=");
        query.append(QUrl::toPercentEncoding(this->passwordHash(this->_password)));
        QString response = http.execute(this->_authUrl, query, result);

        if(result != HttpRequestInterface::NoError) {
          this->_resultCallback->authFailed(GameNetAuthResultInterface::AuthResultCodes::UnknownError);
          return;
        }

        // UNDONE: вынести ошибки из http с сетью
        QDomDocument document;
        document.setContent(response);

        if (!document.setContent(response)) {
          this->_resultCallback->authFailed(GameNetAuthResultInterface::AuthResultCodes::UnknownError);
          return;
        }

        QDomElement responseElement = document.documentElement();
        QDomElement authElement = responseElement.firstChildElement("auth");
        QDomElement userIdElement = authElement.firstChildElement("userId");

        if(userIdElement.isNull()) {
          // ERROR
          this->_resultCallback->authFailed(GameNetAuthResultInterface::AuthResultCodes::UnknownError);
          return;
        }

        this->_cridential.setUserId(userIdElement.text());

        QDomElement appKeyElement = authElement.firstChildElement("appKey");
        if (appKeyElement.isNull()) {
          // ERROR
          this->_resultCallback->authFailed(GameNetAuthResultInterface::AuthResultCodes::UnknownError);
          return;
        }
        this->_cridential.setAppKey(appKeyElement.text());

        QDomElement cookieElement = authElement.firstChildElement("cookie");
        if (cookieElement.isNull()) {
          // ERROR
          this->_resultCallback->authFailed(GameNetAuthResultInterface::AuthResultCodes::UnknownError);
          return;
        }
        this->_cridential.setCookie(cookieElement.text());
        
        this->_resultCallback->authResult(this->_cridential);
      }

    }
  }
}