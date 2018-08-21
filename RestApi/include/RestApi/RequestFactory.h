#pragma once

#include <RestApi/restapi_global.h>

namespace P1 {
  namespace RestApi {
    class RequestBase;

    class RESTAPI_EXPORT RequestFactory
    {
    public:
      enum RequestType {
        Http,
      };

      RequestFactory(void);
      virtual ~RequestFactory(void);

      RequestBase *create(RequestFactory::RequestType type);
    };
  }
}
