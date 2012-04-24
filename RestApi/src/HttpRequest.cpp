/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/HttpRequest.h"

#include <qdatetime.h>

#include <curl/curl.h>
#include <curl/easy.h>

namespace GGS {
  namespace RestApi {

    HttpRequest::HttpRequest() {
    }


    HttpRequest::~HttpRequest() {
    }

    int HttpRequest::curlReadCallback( char *buf, int size, int nmemb, QByteArray *extraData )
    {
      if (extraData == 0)
        return 0;

      int nBytes = size * nmemb;
      extraData->append(buf, nBytes);
      return nBytes;
    }

    int HttpRequest::curlFileDownloadProgress(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
    {
      TimeOutInfo *info = reinterpret_cast<TimeOutInfo*>(ptr);
      if (!info)
        return 0;

      if (abs(info->downloadSize - NowDownloaded) > 0.1) {
        info->downloadSize = NowDownloaded;
        info->lastModifiedTime = QDateTime::currentMSecsSinceEpoch();
      } else {
        if (QDateTime::currentMSecsSinceEpoch() - info->lastModifiedTime > 30000)
          return 1;

      }

      return 0;
    }

    QString HttpRequest::execute( const QString& url, const QString& query, HttpRequestInterface::ResultCodes& resultCode )
    {
      CURL *pointerCurl;
      CURLcode result;

      pointerCurl = curl_easy_init();

      struct curl_slist *slist=NULL;
      slist = curl_slist_append(slist, "Connection: Keep-Alive");  
      slist = curl_slist_append(slist, "Keep-Alive: 300");

      result = curl_easy_setopt(pointerCurl, CURLOPT_HTTPHEADER, slist);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      result = curl_easy_setopt(pointerCurl, CURLOPT_FOLLOWLOCATION, 1);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      result = curl_easy_setopt(pointerCurl, CURLOPT_TIMEOUT, 30);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      result = curl_easy_setopt(pointerCurl, CURLOPT_SSL_VERIFYPEER, 0L);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      result = curl_easy_setopt(pointerCurl, CURLOPT_SSL_VERIFYHOST, 0L);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      result = curl_easy_setopt(pointerCurl, CURLOPT_WRITEFUNCTION, curlReadCallback);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      result = curl_easy_setopt(pointerCurl, CURLOPT_NOPROGRESS, 0);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      result = curl_easy_setopt(pointerCurl, CURLOPT_PROGRESSFUNCTION, curlFileDownloadProgress);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      TimeOutInfo timeoutInfo;
      timeoutInfo.lastModifiedTime = QDateTime::currentMSecsSinceEpoch();
      timeoutInfo.downloadSize = 0;
      result = curl_easy_setopt(pointerCurl, CURLOPT_PROGRESSDATA, &timeoutInfo);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      char *encoding = "gzip";
      result = curl_easy_setopt(pointerCurl, CURLOPT_ACCEPT_ENCODING, encoding);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      QByteArray responseArray;
      result = curl_easy_setopt(pointerCurl, CURLOPT_WRITEDATA, &responseArray);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      bool isGetRequest = (url.length() + query.length() + 1) < 1500;

      QString getUrl = url;
      if(isGetRequest) {
        getUrl.append('?');
        getUrl.append(query);
      }

      QByteArray urlArray = getUrl.toAscii();
      char *urlpointer = urlArray.data();
      result = curl_easy_setopt(pointerCurl, CURLOPT_URL, urlpointer);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      char *post = 0;
      QByteArray postArray;
      if(!isGetRequest) {
        postArray = query.toAscii();
        post = postArray.data();
        result = curl_easy_setopt(pointerCurl, CURLOPT_POSTFIELDS, post);
        if(result != CURLE_OK) {
          resultCode = HttpRequestInterface::CurlError;
          return QString();
        }
      }

      result = curl_easy_perform(pointerCurl);
      if(result != CURLE_OK) {
        resultCode = HttpRequestInterface::CurlError;
        return QString();
      }

      curl_easy_cleanup(pointerCurl);
      curl_slist_free_all(slist);

      resultCode = NoError;
      return QString::fromUtf8(responseArray.data());
    }

  }
}