#ifndef _GGS_RESTAPI_CACHEINTERFACE_H_
#define _GGS_RESTAPI_CACHEINTERFACE_H_

#include "restapi_global.h"
#include <QtCore/QString>

namespace GGS {
  namespace RestApi {
    class RESTAPI_EXPORT CacheInterface {
    public:
      virtual ~CacheInterface() {};
      virtual bool tryGet(const QString& key, QString& value) = 0;
      virtual void put(const QString& key, const QString& value, int timeInSec) = 0;
    };
  }
}


#endif // _GGS_RESTAPI_CACHEINTERFACE_H_