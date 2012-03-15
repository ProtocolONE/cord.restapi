/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_AUTH_GENERICAUTH_H_
#define _GGS_RESTAPI_AUTH_GENERICAUTH_H_

#include "restapi_global.h"
#include "Auth/GameNetAuthInterface.h"
#include "Auth/GameNetAuthResultInterface.h"
#include "GameNetCredential.h"
#include "HttpRequest.h"

#include "curl/curl.h"

#include <QtCore/QtConcurrentRun>
#include <QtCore/QUrl>
#include <QtCore/QCryptographicHash>
#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Auth {
      class RESTAPI_EXPORT GenericAuth : public QObject,
        public GameNetAuthInterface
      {
        Q_OBJECT
      public:
        GenericAuth();
        ~GenericAuth();

        const QString& type() { return this->_methodType; }
        void login();
        void setResultCallback( GameNetAuthResultInterface *result );

        void setAuthUrl(const QString& authUrl) { this->_authUrl = authUrl; } 

      public slots:
        void setLogin(const QString& loginName) { this->_login = loginName; }
        void setPassword(const QString& password) { this->_password = password; }

      private:
        void loginSync();
        QString passwordHash(const QString& password);

        GameNetAuthResultInterface *_resultCallback;
        GameNetCredential _cridential;

        QString _methodType;
        QString _authUrl;
        QString _login;
        QString _password;
      };
    }
  }
}
#endif // _GGS_RESTAPI_AUTH_GENERICAUTH_H_