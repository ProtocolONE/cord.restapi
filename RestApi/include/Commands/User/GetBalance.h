/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDS_USER_GETBALANCE_H_
#define _GGS_RESTAPI_COMMANDS_USER_GETBALANCE_H_

#include "restapi_global.h"
#include "CommandBase.h"

#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        class RESTAPI_EXPORT GetBalance : public QObject,
          public CommandBase
        {
          Q_OBJECT
        public:
          GetBalance();
          ~GetBalance();
          
          virtual bool callMethod( CommandResults commandResultCode, QDomDocument response );
        signals:
          void result(int balance);
        };
      }
    }
  }
}

#endif // _GGS_RESTAPI_COMMANDS_USER_GETBALANCE_H_