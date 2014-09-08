/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

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