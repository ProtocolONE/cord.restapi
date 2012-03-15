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

      GenericAuth::GenericAuth()
      {
        this->_methodType = "generic";
        // UNDONE: ’от€... если считать этот класс в единственном экземпл€ре, то вызвать можно и тут.
        // 19.03.2012  igor.bugaev - инициализаци€ курла остаетс€ здесь до написани€ врапера.

        curl_global_init(CURL_GLOBAL_ALL);
        this->_resultCallback = 0;
      }

      GenericAuth::~GenericAuth()
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
        return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1).toHex());
      }

      void GenericAuth::loginSync()
      {
        HttpRequest http;
        HttpRequestInterface::ResultCodes result;

        QString query("login=");
        query.append(QUrl::toPercentEncoding(this->_login));
        query.append("&passhash=");
        query.append(QUrl::toPercentEncoding(this->passwordHash(this->_password)));
        QString response = http.execute(this->_authUrl, query, result);

        if(result != HttpRequestInterface::NoError) {
          this->_resultCallback->authFailed(GameNetAuthResultInterface::UnknownError);
          return;
        }

        QDomDocument document;
        document.setContent(response);

        if (!document.setContent(response)) {
          this->_resultCallback->authFailed(GameNetAuthResultInterface::UnknownError);
          return;
        }

        QDomElement responseElement = document.documentElement();
        QDomElement errorElement = responseElement.firstChildElement("error");
        QDomElement errorMessage  = errorElement.firstChildElement("message");
        QDomElement errorCode  = errorElement.firstChildElement("code");

        if (!errorMessage.isNull() || !errorCode.isNull()){
          int genericErrorMessageCode = errorCode.text().toInt();          
          if (genericErrorMessageCode == 100)
            this->_resultCallback->authFailed(GameNetAuthResultInterface::WrongLoginOrPassword);
          else
            this->_resultCallback->authFailed(GameNetAuthResultInterface::UnknownError);
          return;
        }

        QDomElement authElement = responseElement.firstChildElement("auth");
        QDomElement userIdElement = authElement.firstChildElement("userId");

        if(userIdElement.isNull()) {
          this->_resultCallback->authFailed(GameNetAuthResultInterface::UnknownError);
          return;
        }

        this->_cridential.setUserId(userIdElement.text());

        QDomElement appKeyElement = authElement.firstChildElement("appKey");
        if (appKeyElement.isNull()) {
          this->_resultCallback->authFailed(GameNetAuthResultInterface::UnknownError);
          return;
        }
        this->_cridential.setAppKey(appKeyElement.text());

        QDomElement cookieElement = authElement.firstChildElement("cookie");
        if (cookieElement.isNull()) {
          this->_resultCallback->authFailed(GameNetAuthResultInterface::UnknownError);
          return;
        }
        this->_cridential.setCookie(cookieElement.text());
        
        this->_resultCallback->authResult(this->_cridential);
      }

    }
  }
}