/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_HTTP_REQUEST_H_
#define _GGS_RESTAPI_HTTP_REQUEST_H_

#include "restapi_global.h"
#include "HttpRequestInterface.h"

#include <QtCore/QString>
#include <QtCore/QDebug>

namespace GGS {
  namespace RestApi {

    class RESTAPI_EXPORT HttpRequest : public HttpRequestInterface
    {
    public:
      HttpRequest();
      ~HttpRequest();

      QString execute( const QString& url, const QString& query, HttpRequestInterface::ResultCodes &resultCode );
    private:
      static int curlReadCallback(char *buf, int size, int nmemb, QByteArray *extraData);
      static int curlFileDownloadProgress(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);
    };

  }
}
#endif // _GGS_RESTAPI_HTTP_REQUEST_H_