/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDS_SERVICE_RESPONSE_DETAILEDSERVICESRESPONSE_H_
#define _GGS_RESTAPI_COMMANDS_SERVICE_RESPONSE_DETAILEDSERVICESRESPONSE_H_

#include <RestApi/restapi_global.h>
#include <RestApi/Commands/Service/Response/DetailedServiceInfo.h>

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