/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <RestApi/RequestFactory.h>
#include <RestApi/RequestBase.h>
#include <RestApi/HttpCommandRequest.h>

#include <QtCore/QDebug>

namespace GGS {
  namespace RestApi {

    RequestFactory::RequestFactory(void)
    {
    }

    RequestFactory::~RequestFactory(void)
    {
    }

    RequestBase *RequestFactory::create(RequestFactory::RequestType type)
    {
      switch(type) {
      case Http:
        return new HttpCommandRequest();
      default:
        qFatal("Unsupported type in RequestFactory::create");
      }

      Q_ASSERT(0);
    }
  }
}