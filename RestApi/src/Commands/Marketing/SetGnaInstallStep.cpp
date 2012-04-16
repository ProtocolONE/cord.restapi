/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/Commands/Marketing/SetGnaInstallStep.h"
#include <qdebug.h>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Marketing {

        SetGnaInstallStep::SetGnaInstallStep(){
          this->appendParameter("method", "user.setGnaInstallStep");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
        }

        SetGnaInstallStep::~SetGnaInstallStep(){
        }

        bool SetGnaInstallStep::callMethod( CommandResults commandResultCode, QDomDocument response ){
          QDomElement el = response.documentElement().firstChildElement("status");

          if(!el.isNull()) {
            emit this->result(el.text() == "ok");
            this->_resultCode = NoError;
            return false;
          } else
            this->_resultCode = this->_resultCode = XmlError;

          emit this->result(0);
          return true;
        }
      }
    }
  }
}