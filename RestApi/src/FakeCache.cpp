/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/FakeCache.h"

namespace GGS {
  namespace RestApi {
    FakeCache::FakeCache() {
    }


    FakeCache::~FakeCache(){
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