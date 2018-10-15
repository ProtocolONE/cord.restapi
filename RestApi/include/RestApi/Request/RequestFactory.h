#pragma once

#include <RestApi/restapi_global.h>

namespace P1 {
  namespace RestApi {
    namespace Request {

      class RequestBase;

      class RESTAPI_EXPORT RequestFactory
      {
      public:
        enum RequestType {
          UrlEncoded,
          Json,
        };

        RequestFactory();
        virtual ~RequestFactory() = default;

        RequestBase *create(int type);
      };
    }
  }
}