#pragma once

#include <RestApi/restapi_global.h>
#include <QtCore/QString>

namespace P1 {
  namespace RestApi {
    class RESTAPI_EXPORT CacheInterface {
    public:
      virtual ~CacheInterface() {};
      virtual bool tryGet(const QString& key, QString& value) = 0;
      virtual void put(const QString& key, const QString& value, int timeInSec) = 0;
    };
  }
}

