#include "Commands\Marketing\SetGnaInstallStep.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Marketing {

        SetGnaInstallStep::SetGnaInstallStep(){
          this->appendParameter("method", "user.setGnaInstallStep");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
        }

        SetGnaInstallStep::~SetGnaInstallStep(){
        }

        void SetGnaInstallStep::resultCallback( CommandResults commandResultCode, QString response ){
         if(commandResultCode != CommandResults::NoError) {
            this->_resultCode = commandResultCode;
            emit this->result(0);
            return;
          }

          QDomDocument doc;
          if (!doc.setContent(response)) {
            this->_resultCode = CommandResults::XmlError;
            emit this->result(0);
            return;
          }

          QDomElement el = doc.documentElement().firstChildElement("result");

          if(!el.isNull()) {
            emit this->result(el.text().toInt());
            return;
          }

          emit this->result(0);
        }
      }
    }
  }
}