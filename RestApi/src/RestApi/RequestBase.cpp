#include <RestApi/RequestBase.h>

namespace P1 {
  namespace RestApi {

    RequestBase::RequestBase(QObject *parent /*= 0*/)
      : QObject(parent)
      , _cache(nullptr)
      , _debugLogEnabled(false)
    {
    }

    RequestBase::~RequestBase()
    {
    }

    void RequestBase::setCache(CacheInterface *cache)
    {
      this->_cache = cache;
    }

    void RequestBase::setDebugLogEnabled(bool value)
    {
      this->_debugLogEnabled = value;
    }

  }
}