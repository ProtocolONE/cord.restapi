#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>
#include <QVector>
#include <QString>

namespace P1 {
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
