#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace User {

        class RESTAPI_EXPORT GetBalance : 
          public CommandBase
        {
          Q_OBJECT
        public:
          GetBalance();
          ~GetBalance();
          
          virtual bool callMethod( const QDomDocument& response );

          int getBalance() { return this->_balance; }
        private:
            int _balance;
        };
      }
    }
  }
}
