/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

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