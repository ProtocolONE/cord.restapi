/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <RestApi/Commands/Games/GetMw2ServerList.h>

#include <QtCore/QMap>
namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Games {

        GetMw2ServerList::GetMw2ServerList(QObject *parent)
          : CommandBase(parent)
        {
          this->appendParameter("method", "games.getMw2ServerList");
          this->appendParameter("version", "2");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
        }

        GetMw2ServerList::~GetMw2ServerList()
        {
        }
      
        const QList<Response::Mw2ServerInfo>& GetMw2ServerList::getServers() const
        {
          return this->_response;
        }
      
        bool GetMw2ServerList::callMethod(const QDomDocument& response)
        {
          QDomElement serverListElement = response.documentElement()
            .firstChildElement("serverList");

          if (serverListElement.isNull())
            return true;

          QMap<QString, int> serverList;

          QDomElement row = serverListElement.firstChildElement("row");
          for (; !row.isNull(); row = row.nextSiblingElement("row")) {

            QDomElement idElement = row.firstChildElement("id");
            QDomElement positionElement = row.firstChildElement("position");
            QDomElement nameElement = row.firstChildElement("name");
            QDomElement addressElement = row.firstChildElement("address");
            QDomElement pinFlagElement = row.firstChildElement("pin");
            QDomElement statusElement = row.firstChildElement("status");

            if (idElement.isNull() || positionElement.isNull() 
              || nameElement.isNull() || addressElement.isNull() 
              || pinFlagElement.isNull() || statusElement.isNull())
              continue;

            Response::Mw2ServerInfo responseEntry;
            responseEntry.setId(idElement.text().toInt());
            responseEntry.setPosition(positionElement.text().toInt());
            responseEntry.setName(nameElement.text());
            responseEntry.setAddress(addressElement.text());
            responseEntry.setPinned(pinFlagElement.text().toInt());
            responseEntry.setStatus(statusElement.text().toInt());

            this->_response.push_back(responseEntry);
            serverList[responseEntry.name()] = this->_response.size() - 1;
          }
          
          QDomElement charListElement  = response.documentElement()
            .firstChildElement("charList");

          if (charListElement.isNull())
            return false;

          row = charListElement.firstChildElement("row");
          for (; !row.isNull(); row = row.nextSiblingElement("row")) {
            QDomElement serverElement = row.firstChildElement("server");
            QDomElement countElement = row.firstChildElement("count");
            
            if (serverElement.isNull() || countElement.isNull())
              continue;

            QString serverName = serverElement.text();
            if (serverList.contains(serverName)) 
              this->_response[serverList[serverName]].setCharCount(countElement.text().toInt());
          }

           return false;
        }
      }
    }
  }
}