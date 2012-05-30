#include <RestApi/RequestBase.h>

namespace GGS {
  namespace RestApi {

    RequestBase::RequestBase(QObject *parent /*= 0*/)
      : _cache(0)
    {
    }

    RequestBase::~RequestBase()
    {
    }

    void RequestBase::setCache(CacheInterface *cache)
    {
      this->_cache = cache;
    }
  }
}