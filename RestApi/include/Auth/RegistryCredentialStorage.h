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