 #ifndef _GGS_RESTAPI_COMMANDS_MARKETING_SETGNAINSTALLSTEP_H_
#define _GGS_RESTAPI_COMMANDS_MARKETING_SETGNAINSTALLSTEP_H_

#include "restapi_global.h"
#include "CommandBase.h"

#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Marketing {

        class RESTAPI_EXPORT SetGnaInstallStep : public QObject,
          public CommandBase
        {
          Q_OBJECT
        public:
          SetGnaInstallStep();
          ~SetGnaInstallStep();
          
          void resultCallback( CommandResults commandResultCode, QString response );
        signals:
          void result(int resultCode);
        };

      }
    }
  }
}

#endif // _GGS_RESTAPI_COMMANDS_MARKETING_SETGNAINSTALLSTEP_H_