#include <RestApi/FakeCache.h>

namespace P1 {
  namespace RestApi {
    FakeCache::FakeCache()
    {
    }

    FakeCache::~FakeCache()
    {
    }

    bool FakeCache::tryGet( const QString& key, QString& value )
    {
      return false;
    }

    void FakeCache::put( const QString& key, const QString& value, int timeInSec )
    {
    }

  }
}