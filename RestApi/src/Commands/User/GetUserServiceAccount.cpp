
#include "RestApi/Commands/User/GetUserServiceAccount.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        GetUserServiceAccount::GetUserServiceAccount()
        {
          this->appendParameter("method", "user.getServiceAccount");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
          this->_response = new Response::UserServiceAccountResponse();
        }

        GetUserServiceAccount::~GetUserServiceAccount()
        {
          delete _response;
        }

        bool GetUserServiceAccount::callMethod(const QDomDocument& response)
        {   
          QDomElement responseElement = response.documentElement();
          QDomElement serviseAccountElement = responseElement.firstChildElement("serviceAccount");

          if(serviseAccountElement.isNull())
            return true;

          QDomElement el = serviseAccountElement.firstChildElement("login");
          if(!el.isNull())
            this->_response->setLogin(el.text());

          el = serviseAccountElement.firstChildElement("password");
          if(!el.isNull())
            this->_response->setPassword(el.text());

          el = serviseAccountElement.firstChildElement("status");
          if(!el.isNull())
            this->_response->setStatus(el.text());

          el = serviseAccountElement.firstChildElement("token");
          if(!el.isNull())
            this->_response->setToken(el.text());

          return false;
        }

        void GetUserServiceAccount::setServiceId(const QString &id)
        {
          this->appendParameter("serviceId", id);
        }
      }
    }
  }
}