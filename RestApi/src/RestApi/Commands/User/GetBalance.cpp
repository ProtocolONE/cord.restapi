#include <RestApi/Commands/User/GetBalance.h>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace User {
        GetBalance::GetBalance() {
          this->appendParameter("method", "user.getSpeedyInfo");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
          this->_balance = -1;
        }

        GetBalance::~GetBalance() {
        }

        bool GetBalance::callMethod( const QDomDocument& response )
        {
          QDomElement balanceElement  = response.documentElement()
            .firstChildElement("speedyInfo")
            .firstChildElement("balance");

          if (balanceElement.isNull())
            return true;

          QString balanceString = balanceElement.text();
          bool res;
          int balance = balanceString.toInt(&res);
          if(!res)
            return true;

          this->_balance = balance;
          return false;
        }
      }
    }
  }
}