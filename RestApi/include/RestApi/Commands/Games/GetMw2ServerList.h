/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDS_GAMES_GETMW2SERVERLIST_H
#define _GGS_RESTAPI_COMMANDS_GAMES_GETMW2SERVERLIST_H

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>
#include <RestApi/Commands/Games/Response/Mw2ServerListResponse.h>

#include <QtXml/QDomDocument>
#include <QtCore/QString>
#include <QtCore/QList>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Games {
        class RESTAPI_EXPORT GetMw2ServerList : public CommandBase
        {
          Q_OBJECT
        public:
          GetMw2ServerList(QObject *parent = 0);
          ~GetMw2ServerList();

          virtual bool callMethod(const QDomDocument& response);

          const QList<Response::Mw2ServerInfo> &getServers() const;
      
        private:
          QList<Response::Mw2ServerInfo> _response;
        };
      }
    }
  }
}
#endif // _GGS_RESTAPI_COMMANDS_GAMES_GETMW2SERVERLIST_H
