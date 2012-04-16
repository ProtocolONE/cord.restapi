/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/Auth/RegistryCredentialStorage.h"

namespace GGS {
  namespace RestApi {
    namespace Auth {

      RegistryCredentialStorage::RegistryCredentialStorage(void)
      {
        this->_settings = new QSettings("HKEY_CURRENT_USER\\Software\\GGS\\GNA\\", QSettings::NativeFormat);
      }


      RegistryCredentialStorage::~RegistryCredentialStorage(void)
      {
      }

      void RegistryCredentialStorage::save( const GameNetCredential& credential )
      {
        this->_settings->setValue("userId", credential.userId());
        this->_settings->setValue("appKey", credential.appKey());
        this->_settings->setValue("cookie", credential.cookie());
      }

      bool RegistryCredentialStorage::tryLoad( GameNetCredential& credential )
      {
        if (!this->_settings->contains("userId")
          || !this->_settings->contains("appKey")
          || !this->_settings->contains("cookie"))
        {
           return false;
        }

        credential.setUserId( this->_settings->value("userId").toString() );
        credential.setAppKey( this->_settings->value("appKey").toString() );
        credential.setCookie( this->_settings->value("cookie").toString() );
        return true;
      }

      void RegistryCredentialStorage::reset()
      {
        this->_settings->remove("userId");
        this->_settings->remove("appKey");
        this->_settings->remove("cookie");
      }

    }
  }
}