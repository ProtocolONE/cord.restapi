/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (�) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

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