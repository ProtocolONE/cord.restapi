/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_CACHEINTERFACE_H_
#define _GGS_RESTAPI_CACHEINTERFACE_H_

#include <RestApi/restapi_global.h>
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