/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef GETCSSERVERLIST_H
#define GETCSSERVERLIST_H

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>
#include <QVector>
#include <QString>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Games {

        struct ServerInfo{
            QString ip;
            int port;
            int usage;
        };

        class RESTAPI_EXPORT GetCSServerList : 
          public CommandBase
        {
          Q_OBJECT
        public:
          GetCSServerList(QObject *parent = 0);
          ~GetCSServerList();
          
          virtual bool callMethod( const QDomDocument& response );

          const QVector<ServerInfo>& getServers() const { return this->_serverList; }
        private:
          QVector<ServerInfo> _serverList;
        };
      }
    }
  }
}

#endif // _GGS_RESTAPI_COMMANDS_GAMES_GETCSSERVERLIST_H