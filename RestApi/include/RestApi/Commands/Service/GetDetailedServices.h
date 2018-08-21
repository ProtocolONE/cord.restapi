#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>
#include <RestApi/Commands/Service/Response/DetailedServiceInfo.h>
#include <RestApi/Commands/Service/Response/DetailedServicesResponse.h>

#include <QtCore/QPointer>
#include <QtCore/QDebug>
#include <QtXml/QDomDocument>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace Service {
        class RESTAPI_EXPORT GetDetailedServices : 
          public CommandBase
        {
          Q_OBJECT
        public:
          GetDetailedServices();
          ~GetDetailedServices();

          virtual bool callMethod( const QDomDocument& response );

          Response::DetailedServicesResponse* response() { return this->_response; }

          void setGroupId(int groudId);

        private:
          QPointer<Response::DetailedServicesResponse> _response;
        };
      }
    }
  }
}
