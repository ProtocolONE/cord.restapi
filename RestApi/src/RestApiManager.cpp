#include "RestApiManager.h"

namespace GGS {
  namespace RestApi {

    RestApiManager::RestApiManager(void)
    {
    }

    RestApiManager::~RestApiManager(void)
    {
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