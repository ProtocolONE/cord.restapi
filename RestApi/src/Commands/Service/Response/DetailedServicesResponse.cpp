/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "Commands/Service/Response/DetailedServicesResponse.h"

namespace GGS {
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