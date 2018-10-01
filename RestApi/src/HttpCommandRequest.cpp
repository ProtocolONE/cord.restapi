/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (�) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "HttpCommandRequest.h"

namespace GGS {
  namespace RestApi {

    HttpCommandRequest::HttpCommandRequest(QObject *parent)
      : QObject(parent)
    {
      // UNDONE: ����... ���� ������� ���� ����� � ������������ ����������, �� ������� ����� � ���.     
      // 19.03.2012 Igor.Bugaev - ������������� curl �������� �� ��������� ��������
      
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

      QString response;
      if (this->_cache->tryGet(request, response)) {
        arguments.command()->resultCallback(CommandBaseInterface::NoError, response);
        return;
      }

      QString restApiurl = command->isRestapiOverrided() ? command->restapiUrl() : arguments.uri();
      HttpRequest http;
      HttpRequestInterface::ResultCodes result;
      response = http.execute(restApiurl, request, result);
      
      arguments.command()->resultCallback(
        result == HttpRequestInterface::NoError 
          ? CommandBaseInterface::NoError 
          : CommandBaseInterface::NetworkError
        , response);
    }
  }
}