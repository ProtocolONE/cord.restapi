/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "Commands/User/GetBalance.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {
        GetBalance::GetBalance() {
          this->appendParameter("method", "user.getSpeedyInfo");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
        }

        GetBalance::~GetBalance() {
        }

        bool GetBalance::resultCallback( CommandResults commandResultCode, QString response )
        {
          if (errorResultParse(commandResultCode, response)){
            emit this->result(0);
            return true;
          }
          QDomDocument doc; doc.setContent(response);
          QDomElement balanceElement  = doc.documentElement()
            .firstChildElement("speedyInfo")
            .firstChildElement("balance");

          if (balanceElement.isNull()) {
            this->_resultCode = XmlError;
            emit this->result(0);
            return true;
          }

          QString balanceString = balanceElement.text();
          bool res;
          int balance = balanceString.toInt(&res);
          if(!res){
            this->_resultCode = XmlError;
            emit this->result(0);
            return true;
          }

          emit this->result(balance);
          return false;
        }
      }
    }
  }
}