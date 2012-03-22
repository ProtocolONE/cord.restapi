/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDS_SERVICE_GETDETAILEDSERVICES_H_
#define _GGS_RESTAPI_COMMANDS_SERVICE_GETDETAILEDSERVICES_H_

#include "restapi_global.h"
#include "CommandBase.h"

#include "Response/DetailedServiceInfo.h"
#include "Response/DetailedServicesResponse.h"

#include <QtCore/QPointer>
#include <QtCore/QDebug>
#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Service {
        class RESTAPI_EXPORT GetDetailedServices : public QObject,
          public CommandBase
        {
          Q_OBJECT
        public:
          GetDetailedServices();
          ~GetDetailedServices();

          virtual bool callMethod( CommandResults commandResultCode, QDomDocument response );

          Response::DetailedServicesResponse* response() { return this->_response; }

        signals:
          void result();
        private:
          QPointer<Response::DetailedServicesResponse> _response;
        };
      }
    }
  }
}
#endif // _GGS_RESTAPI_COMMANDS_SERVICE_GETDETAILEDSERVICES_H_