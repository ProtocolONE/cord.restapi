/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_AUTH_AUTHMANAGER_H_ 
#define _GGS_RESTAPI_AUTH_AUTHMANAGER_H_

#include <RestApi/restapi_global.h>
#include <RestApi/Auth/GameNetAuthResultInterface.h>
#include <RestApi/Auth/GameNetAuthInterface.h>
#include <RestApi/Auth/CredentialStorageInterface.h>

#include <QtCore/QString>
#include <QtCore/QMap>

namespace GGS {
  namespace RestApi {
    namespace Auth {

      class RESTAPI_EXPORT AuthManager : public QObject,
        public GameNetAuthResultInterface
      {
        Q_OBJECT
      public:
        AuthManager();
        ~AuthManager();

        void registerMethod( GameNetAuthInterface *method );

        virtual void authResult( const GameNetCredential& credential );
        virtual void authFailed( GameNetAuthResultInterface::AuthResultCodes resultCode );

        const GameNetCredential& credential() const { return this->_credential; }

        void setCredentialStorage(CredentialStorageInterface *credentialStorage) { this->_credentialStorage = credentialStorage; }

        bool autoSaveAuthSettings() const { return this->_authSaveCredential; }

      public slots:
        void login(const QString& type);
        void autoLogin();
        void logout();

        /// <summary>Sets an automatic save authorisation settings.</summary>
        /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
        /// <param name="isAutoSaved">true if is automatic saved.</param>
        void setAutoSaveAuthSettings(bool isAutoSaved) { 
          if (!isAutoSaved && this->_credentialStorage != 0){
            this->_credentialStorage->reset();
          }

          this->_authSaveCredential = isAutoSaved; 
        }

      signals:
        void started();
        void finishedSuccessfully();
        void error(int resultCode);

      private:
        bool _authSaveCredential;
        GameNetCredential _credential;
        CredentialStorageInterface *_credentialStorage;
        QMap<QString, GameNetAuthInterface *> _registeredMethods;
      };

    }
  }
}
#endif // _GGS_RESTAPI_AUTH_AUTHMANAGER_H_