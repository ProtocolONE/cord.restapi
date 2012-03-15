/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_HTTP_COMMAND_REQUEST_H_
#define _GGS_RESTAPI_HTTP_COMMAND_REQUEST_H_

#include "restapi_global.h"

#include "curl/curl.h"
#include "curl/easy.h"

#include "HttpRequest.h"

#include "CommandBaseInterface.h"
#include "RequestInterface.h"
#include "CommandBaseArgumentWraper.h"
#include "CacheInterface.h"

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QTime>


#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

#include <QtCore/QDebug>

namespace GGS {
  namespace RestApi {

    class RESTAPI_EXPORT HttpCommandRequest : public QObject, public RequestInterface
    {
      Q_OBJECT
    public:
      explicit HttpCommandRequest(QObject *parent = 0);
      ~HttpCommandRequest(void);


      /// <summary>Executes.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="arguments">[in,out] The arguments.</param>
      void execute(CommandBaseArgumentWraper &arguments);

      void setCache(CacheInterface *cache) { this->_cache = cache; }
    private:
      CacheInterface *_cache;
    };

  }
}
#endif // _GGS_RESTAPI_HTTP_COMMAND_REQUEST_H_