#include "Commands/Service/GetDetailedServices.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Service {
        GetDetailedServices::GetDetailedServices(QObject *parrent)
          : QObject(parrent)
        {
          this->appendParameter("method", "service.getDetailedServices");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
        }

        GetDetailedServices::~GetDetailedServices(void)
        {
          if(this->_response) {
            delete this->_response;
          }
        }

        void GetDetailedServices::resultCallback( CommandResults commandResultCode, QString response )
        {
          if(commandResultCode != CommandBaseInterface::NoError) {
            this->_resultCode = commandResultCode;
            emit this->result();
            return;
          }

          this->_response = new Response::DetailedServicesResponse();

          QDomDocument doc;
          if (!doc.setContent(response)) {
            this->_resultCode = CommandBaseInterface::XmlError;
            emit this->result();
            return;
          }

          QDomElement responseElement = doc.documentElement();
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
            return;
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
          // UNDONE finished.
        }

      }
    }
  }
}