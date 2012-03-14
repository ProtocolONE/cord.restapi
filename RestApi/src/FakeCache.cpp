#include "FakeCache.h"

namespace GGS {
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