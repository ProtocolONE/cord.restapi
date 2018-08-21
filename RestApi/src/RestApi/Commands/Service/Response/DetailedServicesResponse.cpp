#include "RestApi/Commands/Service/Response/DetailedServicesResponse.h"

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace Service {
        namespace Response {

          DetailedServicesResponse::DetailedServicesResponse(){
          }


          DetailedServicesResponse::~DetailedServicesResponse()
          {
            QMap<quint64, DetailedServiceInfo*>::iterator end = this->_serviceList.end();
            for (QMap<quint64, DetailedServiceInfo*>::iterator it = this->_serviceList.begin(); it != end; ++it ) {
              delete it.value();
            }
          }

          void DetailedServicesResponse::appendServiceInfo( DetailedServiceInfo *info )
          {
            this->_serviceList.insert(info->id(), info);
          }

          void DetailedServicesResponse::setDetailedInfo( quint64 id, QString name, QString value )
          {
            if(!this->_serviceList.contains(id))
              return;

            DetailedServiceInfo *info = this->_serviceList[id];
            info->appendDetailedInfo(name, value);
          }

        }

      }
    }
  }
}