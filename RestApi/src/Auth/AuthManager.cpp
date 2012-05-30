/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/Auth/AuthManager.h"
#include <QtCore/qdebug.h>


namespace GGS {
  namespace RestApi {
    namespace Auth {

      AuthManager::AuthManager()
      {
        this->_credentialStorage = 0;
      }
      
      AuthManager::~AuthManager()
      {
      }

      void AuthManager::registerMethod(GameNetAuthBase *method)
      {
        Q_CHECK_PTR(method);

        connect(method, SIGNAL(authFailed(GGS::RestApi::Auth::GameNetAuthBase::AuthResultCodes)), 
          this, SLOT(authFailed(GGS::RestApi::Auth::GameNetAuthBase::AuthResultCodes)), 
          Qt::QueuedConnection);

        connect(method, SIGNAL(authResult(GGS::RestApi::GameNetCredential)),
          this, SLOT(authResult(GGS::RestApi::GameNetCredential)), 
          Qt::QueuedConnection);
                
        this->_registeredMethods[method->type()] = method;
      }

      void AuthManager::login(const QString& type )
      {
        if(!this->_registeredMethods.contains(type)) {
          emit this->error(GameNetAuthBase::UnknownAuthMethod);
          qDebug() << " attempt to execute an unknown authentication method (" << type << ")";
          return;
        }

        emit this->started();
        GameNetAuthBase *method = this->_registeredMethods[type];
        method->login();
      }

      void AuthManager::authResult( const GGS::RestApi::GameNetCredential credential )
      {
        this->_credential = credential;
        if (this->_authSaveCredential && this->_credentialStorage != 0) {
          this->_credentialStorage->save(this->_credential);
        }

        emit this->finishedSuccessfully();
      }

      void AuthManager::authFailed( GGS::RestApi::Auth::GameNetAuthBase::AuthResultCodes resultCode )
      {
        emit this->error(static_cast<int>(resultCode));
      }

      void AuthManager::autoLogin()
      {
        if (this->_credentialStorage != 0 && this->_credentialStorage->tryLoad(this->_credential))
          emit this->finishedSuccessfully();
      }

      void AuthManager::logout()
      {
        this->_credential.setAppKey("");
        this->_credential.setUserId("");
        this->_credential.setCookie("");

        if (this->_credentialStorage != 0)
          this->_credentialStorage->reset();
      }

      const GameNetCredential& AuthManager::credential() const
      {
        return this->_credential;
      }

      void AuthManager::setCredentialStorage( CredentialStorageInterface *credentialStorage )
      {
        this->_credentialStorage = credentialStorage;
      }

      bool AuthManager::autoSaveAuthSettings() const
      {
        return this->_authSaveCredential;
      }

      void AuthManager::setAutoSaveAuthSettings( bool isAutoSaved )
      {
        if (!isAutoSaved && this->_credentialStorage != 0){
          this->_credentialStorage->reset();
        }

        this->_authSaveCredential = isAutoSaved;
      }

    }
  }
}