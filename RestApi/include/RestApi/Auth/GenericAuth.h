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

#include <RestApi/restapi_global.h>
#include <RestApi/Auth/GameNetAuthBase.h>

#include <QtCore/QString>
#include <QtCore/QPointer>
#include <QtCore/QList>
#include <QtNetwork/QSslError>

class QNetworkAccessManager;
class QNetworkReply;

namespace GGS {
  namespace RestApi {
    namespace Auth {
      class RESTAPI_EXPORT GenericAuth : public GameNetAuthBase
      {
        Q_OBJECT
      public:
        GenericAuth();
        ~GenericAuth();

        const QString& type();
        void login();
        void setAuthUrl(const QString& authUrl); 

      public slots:
        void setLogin(const QString& loginName);
        void setPassword(const QString& password);
      
      private slots:
        void requestFinish();
        void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

      private:
        QPointer<QNetworkAccessManager> _networkManager;

        QString _methodType;
        QString _authUrl;
        QString _login;
        QString _password;
      };
    }
  }
}
#endif // _GGS_RESTAPI_AUTH_GENERICAUTH_H_