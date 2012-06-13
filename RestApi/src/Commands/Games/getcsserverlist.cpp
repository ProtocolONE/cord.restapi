
#include "RestApi/Commands/Games/getcsserverlist.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Games {

        GetCSServerList::GetCSServerList(QObject *parent)
        {
          this->appendParameter("method", "games.getCSServerList");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(false);
        }

        GetCSServerList::~GetCSServerList()
        {

        }

        bool GetCSServerList::callMethod( const QDomDocument& response )
        {
          QDomElement serverListElement  = response.documentElement()
            .firstChildElement("result");

          if (serverListElement.isNull())
            return true;

           for(QDomElement row = serverListElement.firstChildElement("row"); !row.isNull(); row = row.nextSiblingElement("row")) {
            QDomElement serverElement = row.firstChildElement("server");
            QDomElement usageElement = row.firstChildElement("usage");
            
            if(serverElement.isNull() || usageElement.isNull())
              continue;

            ServerInfo server;
            server.usage = usageElement.text().toInt();
            QString ip = serverElement.text();
            server.ip = ip.left( ip.indexOf(':') );
            server.port = ip.remove(server.ip + ':' ).toInt();

            this->_serverList.push_back(server);
           }

          return false;
        }
      }
    }
  }
}