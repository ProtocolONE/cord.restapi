#ifndef _GGS_RESTAPI_COMMANDS_USER_GETBALANCE_H_
#define _GGS_RESTAPI_COMMANDS_USER_GETBALANCE_H_

#include "restapi_global.h"
#include "CommandBase.h"

#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        class RESTAPI_EXPORT GetBalance : public QObject,
          public CommandBase
        {
          Q_OBJECT
        public:
          GetBalance(void);
          ~GetBalance(void);
          
          void resultCallback( CommandResults commandResultCode, QString response );
        signals:
          void result(int balance);
        };

      }
    }
  }
}

#endif // _GGS_RESTAPI_COMMANDS_USER_GETBALANCE_H_