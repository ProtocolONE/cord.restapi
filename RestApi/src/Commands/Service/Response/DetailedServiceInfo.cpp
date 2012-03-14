#include "Commands/Service/Response/DetailedServiceInfo.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Service {
        namespace Response {
          DetailedServiceInfo::DetailedServiceInfo(void)
          {
          }


          DetailedServiceInfo::~DetailedServiceInfo(void)
          {
          }

          bool DetailedServiceInfo::deserializeMainInfo( const QDomElement &mainInfoRow )
          {
            if(mainInfoRow.isNull()) {
              return false;
            }

            QDomElement serviceIdElement = mainInfoRow.firstChildElement("serv_id");
            if(serviceIdElement.isNull()) {
              return false;
            }


            QString serviceId = serviceIdElement.text();
            bool res;
            this->_id = serviceId.toULongLong(&res);
            if(!res) {
              return false;
            }


            this->_name = mainInfoRow.firstChildElement("serv_name").text();
            this->_serviceUrl = mainInfoRow.firstChildElement("serv_url").text();

            return true;
          }

          bool DetailedServiceInfo::detailedInfo( const QString& name, QString& value )
          {
            if (!this->_detailedInfo.contains(name)) {
              return false;
            }

            value = this->_detailedInfo[name];
            return true;
          }

        }
      }
    }
  }
}