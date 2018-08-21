#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/Commands/Service/Response/DetailedServiceInfo.h>

#include <QtCore/QObject>
#include <QtCore/QMap>

namespace P1 {
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
