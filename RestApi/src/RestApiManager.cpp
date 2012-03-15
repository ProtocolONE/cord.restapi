/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApiManager.h"

namespace GGS {
  namespace RestApi {

    RestApiManager::RestApiManager(){
    }

    RestApiManager::~RestApiManager(){
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
  }
}