/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (�) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDS_USER_GETBALANCE_H_
#define _GGS_RESTAPI_COMMANDS_USER_GETBALANCE_H_

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        class RESTAPI_EXPORT GetBalance : 
          public CommandBase
        {
          Q_OBJECT
        public:
          GetBalance();
          ~GetBalance();
          
          virtual bool callMethod( const QDomDocument& response );

          int getBalance() { return this->_balance; }
        private:
            int _balance;
        };
      }
    }
  }
}

#endif // _GGS_RESTAPI_COMMANDS_USER_GETBALANCE_H_