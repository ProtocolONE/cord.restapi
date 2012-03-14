#ifndef _GGS_RESTAPI_HTTPREQUESTINTERFACE_H_
#define _GGS_RESTAPI_HTTPREQUESTINTERFACE_H_

#include <QtCore/QString>

namespace GGS {
  namespace RestApi {

    /// <summary>HttpRequest interface. Реализация класса обязана быть реинтерабельной.</summary>
    /// <remarks>Ilya.Tkachenko, 13.02.2012.</remarks>
    class HttpRequestInterface{
    public:

      enum ResultCodes {
        NoError = 0,
        UnknownError = 1,
        CurlError = 2,
      };

      virtual ~HttpRequestInterface() {};
      virtual QString execute(const QString& url, const QString& query, HttpRequestInterface::ResultCodes &result) = 0;
    };

  }
}
#endif // _GGS_RESTAPI_HTTPREQUESTINTERFACE_H_