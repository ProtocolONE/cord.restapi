#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/Request/RequestBase.h>

#include <QtCore/QList>
#include <QtCore/QPointer>

class QNetworkAccessManager;

namespace P1 {
  namespace RestApi {
    namespace Request {

      class RESTAPI_EXPORT HttpCommandRequest : public RequestBase
      {
        Q_OBJECT
      public:
        explicit HttpCommandRequest(QObject *parent = 0);
        virtual ~HttpCommandRequest();

        virtual void internalExecute() override;

      private:
        void requestFinish();

        QPointer<QNetworkAccessManager> _networkManager;
        QString _requestString;
      };
    }
  }

}