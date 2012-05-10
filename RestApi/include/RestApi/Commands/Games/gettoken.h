/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef GETTOKEN_H
#define GETTOKEN_H

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>
#include <QVector>
#include <QString>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Games {

        class RESTAPI_EXPORT GetToken : 
          public CommandBase
        {
          Q_OBJECT
        public:
          GetToken(QObject *parent = 0);
          ~GetToken();
          
          void setGameId(const QString& gameId);

          virtual bool callMethod( const QDomDocument& response );

          const QString& getToken() const { return this->_token; }
        private:
          QString _token;
        };
      }
    }
  }
}

#endif // _GGS_RESTAPI_COMMANDS_GAMES_GETCSSERVERLIST_H