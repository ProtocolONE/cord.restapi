/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/Commands/User/GetBalance.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {
        GetBalance::GetBalance() {
          this->appendParameter("method", "user.getSpeedyInfo");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
          this->_balance = -1;
        }

        GetBalance::~GetBalance() {
        }

        bool GetBalance::callMethod( const QDomDocument& response )
        {
          QDomElement balanceElement  = response.documentElement()
            .firstChildElement("speedyInfo")
            .firstChildElement("balance");

          if (balanceElement.isNull())
            return true;

          QString balanceString = balanceElement.text();
          bool res;
          int balance = balanceString.toInt(&res);
          if(!res)
            return true;

          this->_balance = balance;
          return false;
        }
      }
    }
  }
}