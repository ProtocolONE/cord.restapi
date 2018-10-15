#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/Request/RequestBase.h>

#include <QtCore/QObject>
#include <QtCore/QPointer>

class QNetworkAccessManager;

namespace P1 {
  namespace RestApi {
    namespace Request {

      class RESTAPI_EXPORT JsonRequest : public RequestBase
      {
        Q_OBJECT
      public:
        explicit JsonRequest(QObject *parent = 0);
        virtual ~JsonRequest() = default;

        virtual void internalExecute() override;

      private:
        void requestFinish();

        QPointer<QNetworkAccessManager> _networkManager;
      };

    }
  }
}