/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/Commands/Games/gettoken.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Games {

        GetToken::GetToken(QObject *parent)
        {
          this->appendParameter("method", "games.getToken");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
        }

        GetToken::~GetToken()
        {

        }
        bool GetToken::callMethod( const QDomDocument& response )
        {
          QDomElement tokenElement  = response.documentElement()
            .firstChildElement("token");

          if (tokenElement.isNull())
            return true;

          this->_token = tokenElement.text();
          return false;
        }
        void GetToken::setGameId(const QString& gameId){
          this->appendParameter("gameId", gameId);
        }
      }
    }
  }
}