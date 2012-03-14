#ifndef _GGS_RESTAPI_COMMANDS_SERVICE_RESPONSE_DETAILEDSERVICESRESPONSE_H_
#define _GGS_RESTAPI_COMMANDS_SERVICE_RESPONSE_DETAILEDSERVICESRESPONSE_H_

#include "restapi_global.h"

#include "DetailedServiceInfo.h"

#include <QtCore/QObject>
#include <QtCore/QMap>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Service {
        namespace Response {

          class RESTAPI_EXPORT DetailedServicesResponse : public QObject
          {
            Q_OBJECT
          public:
            DetailedServicesResponse(void);
            ~DetailedServicesResponse(void);

            void appendServiceInfo(DetailedServiceInfo *info);
            void setDetailedInfo(quint64 id, QString name, QString value);

            QMap<quint64, DetailedServiceInfo *> serviceList() { return this->_serviceList; }

          private:
            QMap<quint64, DetailedServiceInfo *> _serviceList;
          };
        }
      }
    }
  }
}

#endif // _GGS_RESTAPI_COMMANDS_SERVICE_RESPONSE_DETAILEDSERVICESRESPONSE_H_