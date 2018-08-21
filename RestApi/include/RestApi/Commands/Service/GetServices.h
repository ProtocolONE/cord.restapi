#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace Service {

        class RESTAPI_EXPORT GetServices : public CommandBase
        {
          Q_OBJECT
        public:
          GetServices();
          ~GetServices();

          void setSessionId(const QString& sessionId);
          virtual bool callMethod(const QDomDocument& response) override;
        };

      }
    }
  }
}
