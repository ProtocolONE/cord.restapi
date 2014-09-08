/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#include <RestApi/Commands/Service/GetServices.h>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Service {

        GetServices::GetServices()
        {
          this->appendParameter("method", "service.getServices");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
        }

        GetServices::~GetServices()
        {
        }

        void GetServices::setSessionId(const QString& sessionId)
        {
          this->appendParameter("sessionId", sessionId);
        }

        bool GetServices::callMethod(const QDomDocument& response)
        {
          return false;
        }

      }
    }
  }
}