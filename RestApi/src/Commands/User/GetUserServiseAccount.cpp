#include "Commands/User/GetUserServiseAccount.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        GetUserServiseAccount::GetUserServiseAccount(){
          this->appendParameter("method", "user.getServiceAccount");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);

          _response = NULL;
        }

        GetUserServiseAccount::~GetUserServiseAccount(){
          delete _response;
        }

        void GetUserServiseAccount::resultCallback( CommandResults commandResultCode, QString response ){
          if(commandResultCode != CommandResults::NoError) {
            this->_resultCode = commandResultCode;
            emit this->result();
            return;
          }

          this->_response = new Response::UserServiseAccountResponse();

          QDomDocument doc;
          if (!doc.setContent(response)) {
            this->_resultCode = CommandResults::XmlError;
            emit this->result();
            return;
          }

          QDomElement responseElement = doc.documentElement();
          QDomElement serviseAccountElement = responseElement.firstChildElement("serviceAccount");

          if(serviseAccountElement.isNull()) {
            this->_resultCode = CommandResults::XmlError;
            emit this->result();
            return;
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
        
          this->_resultCode = CommandResults::NoError;
          emit this->result();
        }

      }
    }
  }
}