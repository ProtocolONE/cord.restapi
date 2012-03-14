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
          explicit GetDetailedServices(QObject *parrent = 0);
          ~GetDetailedServices(void);

          virtual void resultCallback( CommandResults commandResultCode, QString response );

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