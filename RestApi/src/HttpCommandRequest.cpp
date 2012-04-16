/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/HttpCommandRequest.h"

#include <curl/curl.h>
#include <curl/easy.h>

namespace GGS {
  namespace RestApi {

    HttpCommandRequest::HttpCommandRequest(QObject *parent)
      : QObject(parent)
    {
      // UNDONE: Хотя... если считать этот класс в единственном экземпляре, то вызвать можно и тут.     
      // 19.03.2012 Igor.Bugaev - инициализация curl остается до написания враппера
      
      curl_global_init(CURL_GLOBAL_ALL);
      this->_cache = 0;
    }

    HttpCommandRequest::~HttpCommandRequest(void)
    {
    }

    void HttpCommandRequest::execute(CommandBaseArgumentWraper &arguments)
    {

      QString request("");
      CommandBaseInterface *command = arguments.command();
      const QMap<QString, QString> *params = command->commandParameters();
      QMap<QString, QString>::const_iterator end = params->end();
      for(QMap<QString, QString>::const_iterator it = params->begin(); it != end; ++it)
      {
        request.append(it.key());
        request.append('=');
        request.append(QUrl::toPercentEncoding(it.value()));
        request.append('&');
      }

      QString response = QString();
      if (this->_cache->tryGet(request, response) ) {
          if (response.size())
            arguments.command()->resultCallback(CommandBaseInterface::NoError, response);
        return;
      }

      QString restApiurl = command->isRestapiOverrided() ? command->restapiUrl() : arguments.uri();
      HttpRequest http;
      HttpRequestInterface::ResultCodes result;
      response = http.execute(restApiurl, request, result);
  
      if (response.size() && result == HttpRequestInterface::NoError) // todo обсудить, правильно ли НЕ вызывать callback если ответ пустой, т.к в этом случае 
      {
        arguments.command()->resultCallback(       // происходит вероятность вызова resultCallback() у абстрактного класса. 
          result == HttpRequestInterface::NoError 
            ? CommandBaseInterface::NoError 
            : CommandBaseInterface::NetworkError
          , response);
      }
    }
  }
}