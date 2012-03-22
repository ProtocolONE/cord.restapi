/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "Commands\User\SetUserActivity.h"
#include <qdebug.h>
#include <qdatetime>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        SetUserActivity::SetUserActivity(){
          this->appendParameter("method", "user.setActivityUser");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
        }

        SetUserActivity::~SetUserActivity(){
        }

        bool SetUserActivity::callMethod( CommandResults commandResultCode, QDomDocument response )
        {
          QDomElement responseElement = response.documentElement();

          if(responseElement.isNull()) {
            this->_resultCode = XmlError;
            emit this->result(0);
            return true;
          }

          QDomElement el = responseElement.firstChildElement("timeout");
          if(!el.isNull()) {
            this->_resultCode = NoError;
            emit this->result(el.text().toInt());
            return false;
          }

          emit this->result(0);
          return true;
        }
      }
    }
  }
}