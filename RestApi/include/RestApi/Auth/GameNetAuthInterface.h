/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_AUTH_GAMENET_AUTHINTERFACE_H_
#define _GGS_RESTAPI_AUTH_GAMENET_AUTHINTERFACE_H_

#include <RestApi/restapi_global.h>
#include <RestApi/Auth/GameNetAuthResultInterface.h>

#include <QtCore/QString>

namespace GGS {
  namespace RestApi {
    namespace Auth {
      class RESTAPI_EXPORT GameNetAuthInterface
      {
      public:
        ~GameNetAuthInterface() {}
        virtual const QString& type() = 0;
        virtual void login() = 0;
        virtual void setResultCallback(GameNetAuthResultInterface *result) = 0;
      };
    }
  }
}
#endif // _GGS_RESTAPI_AUTH_GAMENET_AUTHINTERFACE_H_