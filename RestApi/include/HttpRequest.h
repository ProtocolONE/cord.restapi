#ifndef _GGS_RESTAPI_HTTP_REQUEST_H_
#define _GGS_RESTAPI_HTTP_REQUEST_H_

#include "restapi_global.h"
#include "HttpRequestInterface.h"
#include "curl/curl.h"
#include "curl/easy.h"

#include <QtCore/QString>
#include <QtCore/QDebug>

namespace GGS {
  namespace RestApi {

    class RESTAPI_EXPORT HttpRequest : public HttpRequestInterface
    {
    public:

      HttpRequest(void);
      ~HttpRequest(void);

      QString execute( const QString& url, const QString& query, HttpRequestInterface::ResultCodes &resultCode );
    private:
      static int curlReadCallback(char *buf, int size, int nmemb, QByteArray *extraData);
    };

  }
}
#endif // _GGS_RESTAPI_HTTP_REQUEST_H_