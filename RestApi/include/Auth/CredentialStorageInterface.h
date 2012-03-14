#ifndef _GGS_RESAPI_AUTH_CREDENTIALSTORAGEINTERFACE_H_
#define _GGS_RESAPI_AUTH_CREDENTIALSTORAGEINTERFACE_H_

#include "restapi_global.h"
#include "GameNetCredential.h"

namespace GGS {
  namespace RestApi {
    namespace Auth {

      class RESTAPI_EXPORT CredentialStorageInterface {
      public:
        virtual ~CredentialStorageInterface() {};
        virtual void save(const GameNetCredential& credential) = 0;
        virtual bool tryLoad(GameNetCredential& credential) = 0;
        virtual void reset() = 0;
      };

    }
  }
}

#endif