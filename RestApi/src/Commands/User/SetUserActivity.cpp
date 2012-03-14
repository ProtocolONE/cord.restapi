#include "Commands\User\SeetUserActivity.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        SetUserActivity::SetUserActivity(){
          this->appendParameter("method", "user.setActivityUser");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);

          _response = NULL;
        }

        SetUserActivity::~SetUserActivity(){
          delete _response;
        }

        void SetUserActivity::resultCallback( CommandResults commandResultCode, QString response ){
          if(commandResultCode != CommandResults::NoError) {
            this->_resultCode = commandResultCode;
            emit this->result();
            return;
          }

          this->_response = new Response::UserSetActivityResponse();

          QDomDocument doc;
          if (!doc.setContent(response)) {
            this->_resultCode = CommandResults::XmlError;
            emit this->result();
            return;
          }

          QDomElement responseElement = doc.documentElement();

          if(responseElement.isNull()) {
            this->_resultCode = CommandResults::XmlError;
            emit this->result();
            return;
          }

          QDomElement el = responseElement.firstChildElement("timeout");
          if(!el.isNull()) {
            this->_response->setTimeout(el.text().toInt());
          }
        
          this->_resultCode = CommandResults::NoError;
          emit this->result();
        }

      }
    }
  }
}