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

#include <RestApi/restapi_global.h>
#include <RestApi/Auth/AuthManager.h>
#include <RestApi/Auth/GenericAuth.h>
#include <RestApi/Auth/Vkontakte/VkontakteAuth.h>

#include <QtCore/QDebug>
#include <QtCore/QPointer>
#include <QtDeclarative/QDeclarativeItem>

namespace GGS {
  namespace RestApi {
    namespace Auth {
      class CredentialStorageInterface;

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

        AuthManagerViewModel();
        ~AuthManagerViewModel();

        const QString& accountName() const { return this->_accountName; }
        const QString& password() const { return this->_password; }
        const QString& appKey() const { return this->_appKey; }
        const QString& userId() { return this->_userId; }
        const QString& cookie() { return this->_cookie; }
        bool autoSaveAuth() { return this->_manager.autoSaveAuthSettings(); }

        void setCredentialStorage(CredentialStorageInterface *val);
      public slots:
        void setAccountName(const QString& accountName);
        void setPassword(const QString& password);
        void setAppKey(const QString& appKey);
        void setUserId(const QString& userId);
        void setCookie(const QString& cookie);
        void setAutoSaveAuth(bool autoSaveAuthSettings);

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

        void logoutSuccess();
      private slots:
        void managerAuthStarted();
        void managerAuthFinished();
        void managerAuthError(int resultCode);

      private:
        QString _accountName;
        QString _password;
        
        QString _userId;
        QString _appKey;
        QString _cookie;

        AuthManager _manager;
        Vkontakte::VkontakteAuth _vkauth;
        GenericAuth _genericAuth;
      };
    }
  }
}

#endif // _GGS_RESTAPI_AUTH_AUTHMANAGERVIEWMODEL_H_