#include <RestApi/Request/RequestFactory.h>
#include <RestApi/Request/RequestBase.h>

#include <RestApi/Request/HttpCommandRequest.h>
#include <RestApi/Request/JsonRequest.h>

#include <QtCore/QDebug>

namespace P1 {
  namespace RestApi {
    namespace Request {

      RequestFactory::RequestFactory()
      {
      }

      RequestBase *RequestFactory::create(int type)
      {
        switch (static_cast<RequestFactory::RequestType>(type)) {
        case UrlEncoded:
          return new Request::HttpCommandRequest();
        case Json:
          return new Request::JsonRequest();
        default:
          qFatal("Unsupported type in RequestFactory::create");
        }

        Q_ASSERT(0);
        return 0;
      }
    }
  }
}