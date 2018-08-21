#include <RestApi/Commands/Service/GetServices.h>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace Service {

        GetServices::GetServices()
        {
          this->appendParameter("method", "service.getServices");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
        }

        GetServices::~GetServices()
        {
        }

        void GetServices::setSessionId(const QString& sessionId)
        {
          this->appendParameter("sessionId", sessionId);
        }

        bool GetServices::callMethod(const QDomDocument& response)
        {
          return false;
        }

      }
    }
  }
}