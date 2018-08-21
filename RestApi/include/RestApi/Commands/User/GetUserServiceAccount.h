#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>
#include <RestApi/Commands/User/Response/UserServiceAccountResponse.h>

#include <QtCore/QPointer>
#include <QtXml/QDomDocument>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace User {

        class RESTAPI_EXPORT GetUserServiceAccount : public CommandBase
        {
          Q_OBJECT
        public:
          GetUserServiceAccount();
          ~GetUserServiceAccount();

          void setServiceId(const QString &id);
          void setHwid(const QString &hwid);

          virtual bool callMethod( const QDomDocument& response );

          Response::UserServiceAccountResponse* response() { return this->_response; }

        private:
          Response::UserServiceAccountResponse* _response;
        };

      }
    }
  }
}

