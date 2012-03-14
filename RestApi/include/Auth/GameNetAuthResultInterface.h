/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#ifndef _GGS_RESTAPI_AUTH_GAMENET_AUTHRESULTINTERFACE_H_
#define _GGS_RESTAPI_AUTH_GAMENET_AUTHRESULTINTERFACE_H_

#include "restapi_global.h"
#include "GameNetCredential.h"

namespace GGS {
  namespace RestApi {
    namespace Auth {
      class RESTAPI_EXPORT GameNetAuthResultInterface
      {
      public:

        enum AuthResultCodes {
          Success = 0, // Без ошибок прошла
          UnknownError = 1,
          Cancel = 2, // Например в случаи закрытия окна вконтакта - можно не показывать ошибку.
          NetworkError = 3,
          WrongLoginOrPassword = 4, 
        };

        ~GameNetAuthResultInterface() {}

        virtual void authResult(const GameNetCredential& cridential) = 0;
        virtual void authFailed(AuthResultCodes resultCode) = 0;
      };
    }
  }
}
#endif // _GGS_RESTAPI_AUTH_GAMENET_AUTHRESULTINTERFACE_H_