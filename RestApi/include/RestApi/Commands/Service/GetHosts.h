#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace Service {

        class RESTAPI_EXPORT GetHosts : public CommandBase
        {
          Q_OBJECT
        public:
          explicit GetHosts(QObject *parent = 0);
          virtual ~GetHosts();

          virtual bool callMethod(const QDomDocument& response) override;

          const QList<QMap<QString, QString>>& servicesData();

        private:
          QList<QMap<QString, QString>> _servicesData;
        };

      }
    }
  }
}