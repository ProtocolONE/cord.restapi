/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (�) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Service {

        class RESTAPI_EXPORT GetServices : public CommandBase
        {
          Q_OBJECT
        public:
          GetServices();
          ~GetServices();

          void setSessionId(const QString& sessionId);
          virtual bool callMethod(const QDomDocument& response) override;
        };

      }
    }
  }
}