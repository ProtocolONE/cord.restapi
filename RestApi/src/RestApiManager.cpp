/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <RestApi/CommandBase.h>
#include <RestApi/RequestBase.h>
#include <RestApi/RestApiManager.h>

#include <QtCore/QObject>

namespace GGS {
  namespace RestApi {

    RestApiManager* RestApiManager::_commonInstance;

    RestApiManager::RestApiManager(QObject *parent /*= 0*/) 
      : QObject(parent),
        _cache(0),
        _uri("https://api.gamenet.ru/restapi") 
    {
    }

    RestApiManager::~RestApiManager() {
    }

    void RestApiManager::execute(CommandBase *command)
    {
      Q_CHECK_PTR(command);

      if (command->isAuthRequire()) {
        command->appendParameter("userId", this->_credential.userId());
        command->appendParameter("appKey", this->_credential.appKey());
      }

      if (!command->isRestapiOverrided())
        command->setRestapiUrl(this->_uri);

      RequestBase *request = this->_factory.create(this->_type);
      if (this->_cache) 
        request->setCache(this->_cache);

      connect(request, SIGNAL(finish(GGS::RestApi::CommandBase::CommandResults, QString)),
        command, SLOT(resultCallback(GGS::RestApi::CommandBase::CommandResults, QString)));

      QObject::connect(command, SIGNAL(genericError(GGS::RestApi::CommandBase::Error, QString)), 
        this, SIGNAL(genericError(GGS::RestApi::CommandBase::Error, QString)), Qt::UniqueConnection);
      QMetaObject::invokeMethod(request, 
                                "execute", 
                                Qt::QueuedConnection, 
                                Q_ARG(QUrl, command->url()));
    }

    void RestApiManager::setUri(const QString& uri)
    {
      this->_uri = uri;
    }

    void RestApiManager::setRequest(RequestFactory::RequestType type)
    {
      this->_type = type;
    }

    void RestApiManager::setCridential(const GameNetCredential &credential)
    {
      this->_credential = credential;
    }

    const GameNetCredential &RestApiManager::credential()
    {
      return this->_credential;
    }

    void RestApiManager::setCache(CacheInterface *cache)
    {
      Q_CHECK_PTR(cache);
      this->_cache = cache;
    }

    void RestApiManager::setCommonInstance(RestApiManager *instance)
    {
      Q_CHECK_PTR(instance);
      RestApiManager::_commonInstance = instance;
    }

    RestApiManager* RestApiManager::commonInstance()
    {
      return RestApiManager::_commonInstance;
    }


  }
}