#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/ProtocolOneCredential.h>

namespace P1 {
  namespace RestApi {
    namespace Auth {
      class RESTAPI_EXPORT CredentialStorageInterface
      {
      public:
        virtual ~CredentialStorageInterface() {};
        virtual void save(const ProtocolOneCredential& credential) = 0;
        virtual bool tryLoad(ProtocolOneCredential& credential) = 0;
        virtual void reset() = 0;
      };
    }
  }
}
