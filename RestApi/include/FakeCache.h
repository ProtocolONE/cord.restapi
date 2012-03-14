#ifndef _GGS_RESTAPI_FAKECACHE_H_
#define _GGS_RESTAPI_FAKECACHE_H_

#include "restapi_global.h"
#include "CacheInterface.h"

#include <QtCore/QString>
namespace GGS {
  namespace RestApi {

    class RESTAPI_EXPORT FakeCache : public CacheInterface
    {
    public:
      FakeCache();
      ~FakeCache();

      virtual bool tryGet( const QString& key, QString& value );

      virtual void put( const QString& key, const QString& value, int timeInSec );

    };

  }
}

#endif // _GGS_RESTAPI_FAKECACHE_H_