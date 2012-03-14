/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#ifndef _GGS_RESTAPI_AUTH_AUTHMANAGERVIEWMODEL_H_
#define _GGS_RESTAPI_AUTH_AUTHMANAGERVIEWMODEL_H_

#include "restapi_global.h"
#include "Auth/AuthManager.h"
#include "Auth/GenericAuth.h"
#include "Auth/GameNetAuthResultInterface.h"
#include "Auth/Vkontakte/VkontakteAuth.h"
#include "Auth/RegistryCredentialStorage.h"

#include <QtCore/QPointer>
#include <QtDeclarative/QDeclarativeItem>
#include <QtCore/QDebug>


namespace GGS {
  namespace RestApi {
    namespace Auth {
      class RESTAPI_EXPORT AuthManagerViewModel : public QDeclarativeItem
      {
        Q_OBJECT
        Q_PROPERTY(QString accountName READ accountName WRITE setAccountName NOTIFY accountNameChanged)
        Q_PROPERTY(QString password READ password WRITE setPassword NOTIFY passwordChanged)

        Q_PROPERTY(QString appKey READ appKey NOTIFY appKeyChanged)
        Q_PROPERTY(QString userId READ userId NOTIFY userIdChanged)
        Q_PROPERTY(QString cookie READ cookie NOTIFY cookieChanged)

        Q_PROPERTY(bool autoSaveAuth READ autoSaveAuth WRITE setAutoSaveAuth NOTIFY autoSaveAuthChanged)
      public:

        AuthManagerViewModel(void);
        ~AuthManagerViewModel(void);

        const QString& accountName() const { return this->_accountName; }
        void setAccountName(const QString& accountName);

        const QString& password() const { return this->_password; }
        void setPassword(const QString& password);

        const QString& appKey() const { return this->_appKey; }
        void setAppKey(const QString& appKey);

        const QString& userId() { return this->_userId; }
        void setUserId(const QString& userId);

        const QString& cookie() { return this->_cookie; }
        void setCookie(const QString& cookie);

        bool autoSaveAuth() { return this->_autoSaveAuthSettings; }
        void setAutoSaveAuth(bool autoSaveAuthSettings);

   //     void setAuthManager(GGS::RestApi::Auth::AuthManager *manager) { this->_manager = manager; }
   //     void setGenericAuth(GGS::RestApi::Auth::GenericAuth *genericAuth) { this->_genericAuth = genericAuth; }

      public slots:
        void login(const QString& methodType);
        void autoLogin();
        void logout();

      signals:
        void accountNameChanged();
        void passwordChanged();

        void appKeyChanged();
        void userIdChanged();
        void cookieChanged();

        void autoSaveAuthChanged();
        void authSuccess();
        void authError(int resultCode);

      private slots:
        void managerAuthStarted();
        void managerAuthFinished();
        void managerAuthError(int resultCode);

      private:
   //     QPointer<GGS::RestApi::Auth::AuthManager> _manager;
   //     QPointer<GGS::RestApi::Auth::GenericAuth> _genericAuth;
        bool _autoSaveAuthSettings;
        QString _accountName;
        QString _password;
        
        QString _userId;
        QString _appKey;
        QString _cookie;

        AuthManager _manager;
        Vkontakte::VkontakteAuth _vkauth;
        GenericAuth _genericAuth;
        RegistryCredentialStorage _credentialStorage;
      };

    }
  }
}

#endif // _GGS_RESTAPI_AUTH_AUTHMANAGERVIEWMODEL_H_