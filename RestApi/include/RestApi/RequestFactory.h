/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_REQUESTFACTORY_H_
#define _GGS_RESTAPI_REQUESTFACTORY_H_

#include <RestApi/restapi_global.h>

namespace GGS {
  namespace RestApi {
    class RequestBase;

    class RESTAPI_EXPORT RequestFactory
    {
    public:
      enum RequestType {
        Http,
      };

      RequestFactory(void);
      virtual ~RequestFactory(void);

      RequestBase *create(RequestFactory::RequestType type);
    };
  }
}
#endif //_GGS_RESTAPI_REQUESTFACTORY_H_
