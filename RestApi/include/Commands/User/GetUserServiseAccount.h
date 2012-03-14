#ifndef _GGS_RESTAPI_COMMANDS_USER_GETUSESERVISEACCOUNT_H_
#define _GGS_RESTAPI_COMMANDS_USER_GETUSESERVISEACCOUNT_H_

#include "restapi_global.h"
#include "CommandBase.h"
#include "Response/UserServiseAccountResponse.h"

#include <QtCore/QPointer>
#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        class RESTAPI_EXPORT GetUserServiseAccount : public QObject,
          public CommandBase
        {
          Q_OBJECT
        public:
          GetUserServiseAccount();
          ~GetUserServiseAccount();

          void resultCallback( CommandResults commandResultCode, QString response );

          Response::UserServiseAccountResponse* response() { return this->_response; }

        signals:
          void result();

        private:
          QPointer<Response::UserServiseAccountResponse> _response;
        };

      }
    }
  }
}
#endif