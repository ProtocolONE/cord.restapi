/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <RestApi/RestApiManager.h>

#include <RestApi/CommandBaseInterface.h>
#include <RestApi/HttpCommandRequest.h>
#include <RestApi/CommandBaseArgumentWraper.h>

namespace GGS {
  namespace RestApi {

    RestApiManager::RestApiManager() : _uri("https://api.gamenet.ru/restapi") {
    }

    RestApiManager::~RestApiManager() {
    }

    void RestApiManager::execute( CommandBaseInterface *command )
    {
      if(command->isAuthRequire()) {
        command->appendParameter("userId", this->_credential.userId());
        command->appendParameter("appKey", this->_credential.appKey());
      }

      CommandBaseArgumentWraper wraper;
      wraper.setCommand(command);
      wraper.setUri(this->_uri);

      QtConcurrent::run(this->_request, &RequestInterface::execute, wraper);
    }

    void RestApiManager::setUri( const QString& uri )
    {
      this->_uri = uri;
    }

    void RestApiManager::setRequest( RequestInterface *request )
    {
      this->_request = request;
    }

    void RestApiManager::setCridential( const GameNetCredential &credential )
    {
      this->_credential = credential;
    }

    const GameNetCredential & RestApiManager::credential()
    {
      return this->_credential;
    }
  }
}