/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESAPI_AUTH_VKONTAKTE_VKONTATKEAUTH_H_
#define _GGS_RESAPI_AUTH_VKONTAKTE_VKONTATKEAUTH_H_

#include "restapi_global.h"
#include "GameNetCredential.h"
#include "Auth/GameNetAuthInterface.h"
#include "Auth/GameNetAuthResultInterface.h"

#include "Auth/Vkontakte/UserAgentWebPage.h"
#include "Auth/Vkontakte/VkontakteWebView.h"

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QUrl>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QSslError>
#include <QtNetwork/QNetworkAccessManager>

namespace GGS {
  namespace RestApi {
    namespace Auth {
      namespace Vkontakte {

        class RESTAPI_EXPORT VkontakteAuth : public QObject, public GameNetAuthInterface
        {
          Q_OBJECT

        public:
          VkontakteAuth(void);
          virtual ~VkontakteAuth(void);

          virtual const QString& type() { return this->_methodType; }

          virtual void login();
          virtual void setResultCallback( GameNetAuthResultInterface *result );

          void setTitleUrlHost(const QString& titleUrlHost) { this->_titleUrlHost = titleUrlHost; }
          void setAuthReturnPath(const QString& authReturnPath) { this->_authReturnPath = authReturnPath; }
          void setApplicationId(const QString& applicationId) { this->_applicationId = applicationId; }

        private slots:
          void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);
          void webPageLoadFinished(bool ok);
          void webPageTitleChanged(QString title);
          void webPageClosed();

        private:
          void setAuthResult( bool isSuccess );

          QString _methodType;

          VkontakteWebView *_view;
          UserAgentWebPage *_userPage;

          GameNetCredential _credential;
          GameNetAuthResultInterface *_resultCallback;

          QString _titleUrlHost;
          QString _authReturnPath;
          QString _applicationId;

          QMutex _authStartedLock;
          bool _isAuthStarted;
        };

      }
    }
  }
}

#endif // _GGS_RESAPI_AUTH_VKONTAKTE_VKONTATKEAUTH_H_