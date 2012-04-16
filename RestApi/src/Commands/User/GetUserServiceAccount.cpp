
#include "RestApi/Commands/User/GetUserServiceAccount.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        GetUserServiceAccount::GetUserServiceAccount(){
          this->appendParameter("method", "user.getServiceAccount");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);

          _response = 0;
        }

        GetUserServiceAccount::~GetUserServiceAccount(){
          delete _response;
        }

        bool GetUserServiceAccount::callMethod( CommandResults commandResultCode, QDomDocument response ){
          this->_response = new Response::UserServiceAccountResponse();

          QDomElement responseElement = response.documentElement();
          QDomElement serviseAccountElement = responseElement.firstChildElement("serviceAccount");

          if(serviseAccountElement.isNull()) {
            this->_resultCode = XmlError;
            emit this->result();
            return true;
          }

          QDomElement el = serviseAccountElement.firstChildElement("login");
          if(!el.isNull()) {
            this->_response->setLogin(el.text());
          }

          el = serviseAccountElement.firstChildElement("password");
          if(!el.isNull()) {
            this->_response->setPassword(el.text());
          }

          el = serviseAccountElement.firstChildElement("status");
          if(!el.isNull()) {
            this->_response->setStatus(el.text());
          }

          el = serviseAccountElement.firstChildElement("token");
          if(!el.isNull()) {
            this->_response->setToken(el.text());
          }

          this->_resultCode = NoError;
          emit this->result();
          return false;
        }

        void GetUserServiceAccount::setServiceId( const QString &id )
        {
          this->appendParameter("serviceId", id);
        }
      }
    }
  }
}