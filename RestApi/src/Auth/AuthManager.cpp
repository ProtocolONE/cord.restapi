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

      AuthManager::AuthManager(void)
      {
        this->_credentialStorage = 0;
      }


      AuthManager::~AuthManager(void)
      {
      }

      void AuthManager::registerMethod( GameNetAuthInterface *method )
      {
        method->setResultCallback(this);
        this->_registeredMethods[method->type()] = method;
      }

      void AuthManager::login( const QString& type )
      {
        if(!this->_registeredMethods.contains(type)) {
          emit this->error(GameNetAuthResultInterface::UnknownAuthMethod);
          qDebug() << " attempt to execute an unknown authentication method (" << type << ")";
          return;
        }

        emit this->started();
        GameNetAuthInterface *method = this->_registeredMethods[type];
        method->login();
      }

      void AuthManager::authResult( const GameNetCredential& credential )
      {
        this->_credential = credential;
        if (this->_authSaveCredential && this->_credentialStorage != 0) {
          this->_credentialStorage->save(this->_credential);
        }

        emit this->finishedSuccessfully();
      }

      void AuthManager::authFailed(GameNetAuthResultInterface::AuthResultCodes resultCode)
      {
        emit this->error(static_cast<int>(resultCode));
      }

      void AuthManager::autoLogin()
      {
        if (this->_credentialStorage != 0 && this->_credentialStorage->tryLoad(this->_credential)) {
          emit this->finishedSuccessfully();
        }
      }

      void AuthManager::logout()
      {
        this->_credential.setAppKey("");
        this->_credential.setUserId("");
        this->_credential.setCookie("");

        if (this->_credentialStorage != 0)
          this->_credentialStorage->reset();
      }

    }
  }
}