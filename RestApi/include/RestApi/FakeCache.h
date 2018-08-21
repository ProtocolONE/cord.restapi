#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CacheInterface.h>

#include <QtCore/QString>
namespace P1 {
  namespace RestApi {

    class RESTAPI_EXPORT FakeCache : public CacheInterface
    {
    public:
      FakeCache();
      virtual ~FakeCache();

      virtual bool tryGet( const QString& key, QString& value );

      virtual void put( const QString& key, const QString& value, int timeInSec );

    };

  }
}
