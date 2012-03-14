#ifndef _GGS_RESTAPI_COMMANDS_USER_GETUSERMAININFO_H_
#define _GGS_RESTAPI_COMMANDS_USER_GETUSERMAININFO_H_

#include "restapi_global.h"
#include "CommandBase.h"
#include "Response/UserMainInfoResponse.h"

#include <QtCore/QPointer>
#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        class RESTAPI_EXPORT GetUserMainInfo : public QObject,
          public CommandBase
        {
          Q_OBJECT
        public:
          GetUserMainInfo(void);
          ~GetUserMainInfo(void);

          void resultCallback( CommandResults commandResultCode, QString response );

          Response::UserMainInfoResponse* response() { return this->_response; }

        signals:
          void result();

        private:
          QPointer<Response::UserMainInfoResponse> _response;
        };

      }
    }
  }
}
#endif // _GGS_RESTAPI_COMMANDS_USER_GETUSERMAININFO_H_