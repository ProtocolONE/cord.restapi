#pragma once

#include <RestApi/restapi_global.h>

#include <QtCore/QObject>
#include <QtCore/QHash>
#include <QtXml/QDomDocument>


namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace Service {
        namespace Response {

          class RESTAPI_EXPORT DetailedServiceInfo : public QObject
          {
            Q_OBJECT
          public:
            DetailedServiceInfo();
            ~DetailedServiceInfo();

            void setId(quint64 id) { this->_id = id; }
            quint64 id() { return this->_id; }

            void setName(const QString& name) { this->_name = name; }
            const QString& name() { return this->_name; }

            void setServiceUrl(const QString& serviceUrl) { this->_serviceUrl = serviceUrl; }
            const QString& serviceUrl() { return this->_serviceUrl; }
            
            void appendDetailedInfo(const QString& name, const QString& value) { this->_detailedInfo.insert(name,value); }
            
            bool detailedInfo(const QString& name, QString& value);

            bool deserializeMainInfo(const QDomElement &mainInfoRow);

          private:
            quint64 _id;
            QString _name;
            QString _serviceUrl;

            QHash<QString, QString> _detailedInfo;
          };
        }
      }
    }
  }
}
