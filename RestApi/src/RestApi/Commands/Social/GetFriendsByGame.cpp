#include <RestApi/Commands/Social/GetFriendsByGame.h>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Social {

        GetFriendsByGame::GetFriendsByGame(const QStringList& gameId, QObject *parent)
          : CommandBase(parent)
        {
          this->_gameId = gameId;

          this->appendParameter("method", "social.getFriendsByGame");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "qgna_ru");
          this->appendParameter("gameId", gameId.join(","));
          this->setAuthRequire(true);
        }

        GetFriendsByGame::GetFriendsByGame(QObject *parent)
          : CommandBase(parent)
        {
          this->appendParameter("method", "social.getFriendsByGame");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "qgna_ru");
          this->setAuthRequire(true);
        }

        GetFriendsByGame::~GetFriendsByGame()
        {
        }

        bool GetFriendsByGame::callMethod(const QDomDocument& response)
        {
          QDomElement responseElement = response.documentElement();
          QDomElement friendsByGameElement = responseElement.firstChildElement("friendsByGame");

          if (friendsByGameElement.isNull())
            return true;

          for(QDomElement firstRow = friendsByGameElement.firstChildElement("row"); 
            !firstRow.isNull(); 
            firstRow = firstRow.nextSiblingElement("row")) 
          {
            QDomElement gameIdElement = firstRow.firstChildElement("gameId");
            QDomElement friendsElement = firstRow.firstChildElement("friends");
            
            if (gameIdElement.isNull())
              return true;

            for(QDomElement secondRow = friendsElement.firstChildElement("row"); 
              !secondRow.isNull(); 
              secondRow = secondRow.nextSiblingElement("row")) 
            {
              QDomElement userIdDom = secondRow.firstChildElement("userId");
              QDomElement server = secondRow.firstChildElement("server");
              
              if (userIdDom.isNull())
                continue;

              UserIdWithServer userIdWithServer;
              userIdWithServer.first = userIdDom.text();
              userIdWithServer.second = server.text();

              this->_response.insert(gameIdElement.text(), userIdWithServer);
            } 
          }

          return false;
        }

        const FriendsInGamesMap& GetFriendsByGame::response()
        {
          return this->_response;
        }
        
        void GetFriendsByGame::setGameId(const QStringList& gameId)
        {
          this->_gameId = gameId;
          this->appendParameter("gameId", gameId.join(","));
        }

        const QStringList& GetFriendsByGame::gameId() const
        {
          return this->_gameId;
        }
      }
    }
  }
}