#include <RestApi/RequestFactory.h>
#include <RestApi/RequestBase.h>
#include <RestApi/HttpCommandRequest.h>

#include <QtCore/QDebug>

namespace P1 {
  namespace RestApi {

    RequestFactory::RequestFactory(void)
    {
    }

    RequestFactory::~RequestFactory(void)
    {
    }

    RequestBase *RequestFactory::create(RequestFactory::RequestType type)
    {
      switch(type) {
      case Http:
        return new HttpCommandRequest();
      default:
        qFatal("Unsupported type in RequestFactory::create");
      }

      Q_ASSERT(0);
      return 0;
    }
  }
}