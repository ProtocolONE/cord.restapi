 #ifndef _GGS_RESTAPI_COMMANDS_USER_SETUSERACTIVITY_H_
#define _GGS_RESTAPI_COMMANDS_USER_SETUSERACTIVITY_H_

#include "restapi_global.h"
#include "CommandBase.h"
#include "Response/UserSetActivityResponse.h"

#include <QtCore/QPointer>
#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        class RESTAPI_EXPORT SetUserActivity : public QObject,
          public CommandBase
        {
          Q_OBJECT
        public:
          SetUserActivity();
          ~SetUserActivity();

          void resultCallback( CommandResults commandResultCode, QString response );

          Response::UserSetActivityResponse* response() { return this->_response; }

        signals:
          void result();

        private:
          QPointer<Response::UserSetActivityResponse> _response;
        };

      }
    }
  }
}
#endif