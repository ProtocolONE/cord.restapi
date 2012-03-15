/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_AUTH_REGISTRYCREDENTIALSTORAGE_H_
#define _GGS_RESTAPI_AUTH_REGISTRYCREDENTIALSTORAGE_H_

#include "restapi_global.h"
#include "GameNetCredential.h"
#include "Auth/CredentialStorageInterface.h"

#include <QtCore/QSettings>

namespace GGS {
  namespace RestApi {
    namespace Auth {

      class RESTAPI_EXPORT RegistryCredentialStorage : 
        public QObject, 
        public GGS::RestApi::Auth::CredentialStorageInterface
      {
        Q_OBJECT
      public:
        RegistryCredentialStorage(void);
        ~RegistryCredentialStorage(void);

        virtual void save( const GameNetCredential& credential );

        virtual bool tryLoad( GameNetCredential& credential );

        virtual void reset();

      private:
        QSettings *_settings;
      };

    }
  }
}

#endif // _GGS_RESTAPI_AUTH_REGISTRYCREDENTIALSTORAGE_H_