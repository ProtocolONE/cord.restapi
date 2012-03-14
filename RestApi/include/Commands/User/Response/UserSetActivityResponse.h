#ifndef _GGS_RESTAPI_COMMANDS_USER_RESPONSE_USERACTIVITYRESPONSE_H_
#define _GGS_RESTAPI_COMMANDS_USER_RESPONSE_USERACTIVITYRESPONSE_H_

#include "restapi_global.h"
#include <QtCore/QObject>
#include <QtCore/QString>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {
        namespace Response {

          class RESTAPI_EXPORT UserSetActivityResponse : public QObject
          {
            Q_OBJECT
          public:
            UserSetActivityResponse();
            ~UserSetActivityResponse();

            void setTimeout(quint32 timeout) { _timeout = timeout; }
            quint32 getTimeout() { return _timeout; }

          private:
            quint32 _timeout;
          };
        }
      }
    }
  }
}

#endif