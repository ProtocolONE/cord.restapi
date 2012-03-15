/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "Auth/AuthManagerViewModel.h"
#include <QtCore/QDebug>
namespace GGS {
  namespace RestApi {
    namespace Auth {

      AuthManagerViewModel::AuthManagerViewModel(void)
      {
        this->_vkauth.setApplicationId("2452628");
        this->_vkauth.setAuthReturnPath("http://www.gamenet.ru/virality/auth");
        this->_vkauth.setTitleUrlHost("gnlogin.ru");

        this->_manager.setCredentialStorage(&_credentialStorage);
        this->_manager.registerMethod(&_vkauth);
        
        this->_genericAuth.setAuthUrl("https://gnlogin.ru/");
        this->_manager.registerMethod(&_genericAuth);

        qDebug() << QObject::connect(&this->_manager, SIGNAL(started()), this, SLOT(managerAuthStarted()));
        qDebug() << QObject::connect(&this->_manager, SIGNAL(finishedSuccessfully()), this, SLOT(managerAuthFinished()));
        qDebug() << QObject::connect(&this->_manager, SIGNAL(error(int)), this, SLOT(managerAuthError(int)));
      }

      AuthManagerViewModel::~AuthManagerViewModel(void)
      {
      }

      void AuthManagerViewModel::login( const QString& methodType )
      {
        this->_manager.login(methodType);
      }

      void AuthManagerViewModel::setAccountName( const QString& accountName )
      { 
        if (accountName != this->_accountName) {

          this->_accountName = accountName; 

          this->_genericAuth.setLogin(this->_accountName);

          emit this->accountNameChanged();
        }
      }

      void AuthManagerViewModel::setPassword( const QString& password )
      { 
        if (this->_password != password) {
          this->_password = password; 

          this->_genericAuth.setPassword(this->_password);

          emit this->passwordChanged();
        }
      }

      void AuthManagerViewModel::managerAuthStarted()
      {

      }

      void AuthManagerViewModel::managerAuthFinished()
      {
        this->setUserId(this->_manager.credential().userId());
        this->setAppKey(this->_manager.credential().appKey());
        this->setCookie(this->_manager.credential().cookie());
        emit this->authSuccess();
      }

      void AuthManagerViewModel::managerAuthError(int resultCode)
      {
        this->setUserId(0);
        this->setAppKey("");
        emit this->authError(resultCode);
      }

      void AuthManagerViewModel::setAppKey( const QString& appKey )
      {
        if (this->_appKey != appKey) {
          this->_appKey = appKey; 
          emit this->appKeyChanged();
        }
      }

      void AuthManagerViewModel::setUserId( const QString&  userId )
      {
        if (this->_userId != userId) {
          this->_userId = userId; 
          emit this->userIdChanged();
        }
      }

      void AuthManagerViewModel::setCookie( const QString&  cookie )
      {
        if (this->_cookie != cookie) {
          this->_cookie = cookie; 
          emit this->cookieChanged();
        }
      }

      void AuthManagerViewModel::setAutoSaveAuth( bool autoSaveAuthSettings )
      {       
        if (this->_autoSaveAuthSettings != autoSaveAuthSettings) {
          this->_autoSaveAuthSettings = autoSaveAuthSettings; 
          this->_manager.setAutoSaveAuthSettings(autoSaveAuthSettings);
          emit this->autoSaveAuthChanged();
        }
      }

      void AuthManagerViewModel::autoLogin()
      {
        this->_manager.autoLogin();
      }

      void AuthManagerViewModel::logout()
      {
        this->_manager.logout();
      }

    }
  }
}