/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/Commands/Service/GetDetailedServices.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Service {
        GetDetailedServices::GetDetailedServices()
        {
          this->appendParameter("method", "service.getDetailedServices");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
		      this->_response = 0;
        }

        GetDetailedServices::~GetDetailedServices()
        {
            delete this->_response;
        }

        bool GetDetailedServices::callMethod( CommandResults commandResultCode, QDomDocument response )
        {
          this->_response = new Response::DetailedServicesResponse();
          QDomElement responseElement = response.documentElement();
          QDomElement serviceListElement = responseElement.firstChildElement("serviceList");

          for(QDomElement row = serviceListElement.firstChildElement("row"); !row.isNull(); row = row.nextSiblingElement("row")) {
            Response::DetailedServiceInfo *info = new Response::DetailedServiceInfo();
            if(!info->deserializeMainInfo(row)) {
              delete info;
              continue;
            }

            this->_response->appendServiceInfo(info);
          }

          QDomElement serviceDetailElement = responseElement.firstChildElement("serviceDetail");
          if(serviceDetailElement.isNull()) {
            this->_resultCode = CommandBaseInterface::NoError;
            emit this->result();
            return true;
          }

          for(QDomElement row = serviceDetailElement.firstChildElement("row"); !row.isNull(); row = row.nextSiblingElement("row")) {
            QDomElement serviceIdElement = row.firstChildElement("servinfo_serv_id");
            if(serviceIdElement.isNull())
              continue;

            bool res;
            quint64 id = serviceIdElement.text().toULongLong(&res);
            if(!res)
              continue;

            QDomElement refCodeElement = row.firstChildElement("ref_code");
            if(refCodeElement.isNull())
              continue;
            
            QDomElement servinfoValueElement = row.firstChildElement("servinfo_value");
            if(servinfoValueElement.isNull())
              continue;

            this->_response->setDetailedInfo(id, refCodeElement.text(), servinfoValueElement.text());
          }

          this->_resultCode = CommandBaseInterface::NoError;
          emit this->result();
          return false;
        }
      }
    }
  }
}