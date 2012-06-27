/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDS_SOCIAL_GETFRIENDSBYNAME_H_
#define _GGS_RESTAPI_COMMANDS_SOCIAL_GETFRIENDSBYNAME_H_

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>
#include <QtCore/QStringList>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Social {

       typedef QPair<QString, QString> UserIdWithServer;
       typedef QMultiMap<QString, UserIdWithServer> FriendsInGamesMap;

        class RESTAPI_EXPORT GetFriendsByGame : public CommandBase
        {
          Q_OBJECT

        public:
          GetFriendsByGame(const QStringList& gameId, QObject *parent = 0);
          GetFriendsByGame(QObject *parent = 0);
          ~GetFriendsByGame();

          /*
            Для указание более чем одной игры, используйте запятую как разделитель
            например setGameId("631,71);
          */
          void setGameId(const QStringList& gameId);
          const QStringList& gameId() const;

          virtual bool callMethod(const QDomDocument& response);

          const FriendsInGamesMap& response();

        private:
          QStringList _gameId;
          FriendsInGamesMap _response;
        };
      }
    }
  }
}

#endif // _GGS_RESTAPI_COMMANDS_SOCIAL_GETFRIENDSBYNAME_H_
