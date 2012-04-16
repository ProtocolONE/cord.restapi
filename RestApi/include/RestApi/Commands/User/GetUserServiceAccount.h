/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDS_USER_GETUSESERVICEACCOUNT_H_
#define _GGS_RESTAPI_COMMANDS_USER_GETUSESERVICEACCOUNT_H_

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>
#include <RestApi/Commands/User/Response/UserServiceAccountResponse.h>

#include <QtCore/QPointer>
#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        class RESTAPI_EXPORT GetUserServiceAccount : public QObject,
          public CommandBase
        {
          Q_OBJECT
        public:
          GetUserServiceAccount();
          ~GetUserServiceAccount();

          inline void setServiceId(const QString &id);

          virtual bool callMethod( CommandResults commandResultCode, QDomDocument response );

          Response::UserServiceAccountResponse* response() { return this->_response; }

        signals:
          void result();

        private:
          Response::UserServiceAccountResponse* _response;
        };

      }
    }
  }
}
#endif