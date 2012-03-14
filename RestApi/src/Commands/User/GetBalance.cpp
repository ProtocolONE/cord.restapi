#include "Commands/User/GetBalance.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {
        GetBalance::GetBalance(void)
        {
          this->appendParameter("method", "user.getSpeedyInfo");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
        }

        GetBalance::~GetBalance(void)
        {
        }

        void GetBalance::resultCallback( CommandResults commandResultCode, QString response )
        {
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

          QDomElement balanceElement  = doc.documentElement()
             .firstChildElement("speedyInfo")
             .firstChildElement("balance");

          if (balanceElement.isNull()) {
            this->_resultCode = CommandResults::XmlError;
            emit this->result(0);
            return;
          }

          QString balanceString = balanceElement.text();
          bool res;
          int balance = balanceString.toInt(&res);
          if(!res){
            this->_resultCode = CommandResults::XmlError;
            emit this->result(0);
            return;
          }

          emit this->result(balance);

        }

      }
    }
  }
}