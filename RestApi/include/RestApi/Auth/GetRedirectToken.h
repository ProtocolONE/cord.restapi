#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtCore/QPointer>
#include <QtXml/QDomDocument>

namespace P1 {
  namespace RestApi {
    namespace Auth {

      class RESTAPI_EXPORT GetRedirectToken :
        public CommandBase
      {
        Q_OBJECT
      public:
        GetRedirectToken(QObject *parent = 0);
        ~GetRedirectToken();

        virtual bool callMethod(const QDomDocument& response);

        const QString& token() const;

      private:
        QString _token;
      };

    }
  }
}
