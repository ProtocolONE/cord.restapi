#include "HttpRequest.h"

namespace GGS {
  namespace RestApi {

    HttpRequest::HttpRequest(void)
    {
    }


    HttpRequest::~HttpRequest(void)
    {
    }

    int HttpRequest::curlReadCallback( char *buf, int size, int nmemb, QByteArray *extraData )
    {
      if (extraData == 0)
      {
        return 0;
      }

      int nBytes = size * nmemb;
      extraData->append(buf, nBytes);
      return nBytes;
    }

    QString HttpRequest::execute( const QString& url, const QString& query, HttpRequestInterface::ResultCodes& resultCode )
    {

      CURL *pointerCurl;
      CURLcode result;

      pointerCurl = curl_easy_init();

      struct curl_slist *slist=NULL;
      slist = curl_slist_append(slist, "Connection: Keep-Alive");  
      slist = curl_slist_append(slist, "Keep-Alive: 300");
      // UNDONE: вытставить редирект и праивльные такмймауты. Вожно подписаться на прогресс колл бек для аборта по таймауту
      result = curl_easy_setopt(pointerCurl, CURLOPT_HTTPHEADER, slist);
      if(result != CURLcode::CURLE_OK) {
        resultCode = HttpRequestInterface::ResultCodes::CurlError;
        return QString();
      }

      result = curl_easy_setopt(pointerCurl, CURLOPT_SSL_VERIFYPEER, 0L);
      if(result != CURLcode::CURLE_OK) {
        resultCode = HttpRequestInterface::ResultCodes::CurlError;
        return QString();
      }

      result = curl_easy_setopt(pointerCurl, CURLOPT_SSL_VERIFYHOST, 0L);
      if(result != CURLcode::CURLE_OK) {
        resultCode = HttpRequestInterface::ResultCodes::CurlError;
        return QString();
      }

      result = curl_easy_setopt(pointerCurl, CURLOPT_WRITEFUNCTION, curlReadCallback);
      if(result != CURLcode::CURLE_OK) {
        resultCode = HttpRequestInterface::ResultCodes::CurlError;
        return QString();
      }

      char *encoding = "gzip";
      result = curl_easy_setopt(pointerCurl, CURLOPT_ACCEPT_ENCODING, encoding);
      if(result != CURLcode::CURLE_OK) {
        resultCode = HttpRequestInterface::ResultCodes::CurlError;
        return QString();
      }

      QByteArray responseArray;
      result = curl_easy_setopt(pointerCurl, CURLOPT_WRITEDATA, &responseArray);
      if(result != CURLcode::CURLE_OK) {
        resultCode = HttpRequestInterface::ResultCodes::CurlError;
        return QString();
      }

      bool isGetRequest = (url.length() + query.length() + 1) < 1500;
      //bool isGetRequest = false;
      
      QString getUrl = url;
      if(isGetRequest) {
        getUrl.append('?');
        getUrl.append(query);
      }

      QByteArray urlArray = getUrl.toAscii();
      char *urlpointer = urlArray.data();
      result = curl_easy_setopt(pointerCurl, CURLOPT_URL, urlpointer);
      if(result != CURLcode::CURLE_OK) {
        resultCode = HttpRequestInterface::ResultCodes::CurlError;
        return QString();
      }

      char *post = 0;
      QByteArray postArray;
      if(!isGetRequest) {
        postArray = query.toAscii();
        post = postArray.data();
        result = curl_easy_setopt(pointerCurl, CURLOPT_POSTFIELDS, post);
        if(result != CURLcode::CURLE_OK) {
          resultCode = HttpRequestInterface::ResultCodes::CurlError;
          return QString();
        }
      }

      result = curl_easy_perform(pointerCurl);
      if(result != CURLcode::CURLE_OK) {
        resultCode = HttpRequestInterface::ResultCodes::CurlError;
        return QString();
      }

      curl_easy_cleanup(pointerCurl);
      curl_slist_free_all(slist);

      resultCode = ResultCodes::NoError;
      return QString::fromUtf8(responseArray.data());
    }

  }
}