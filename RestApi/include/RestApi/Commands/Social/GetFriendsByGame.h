#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>
#include <QtCore/QStringList>

namespace P1 {
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

