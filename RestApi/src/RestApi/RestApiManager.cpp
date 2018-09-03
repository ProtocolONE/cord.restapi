#include <RestApi/CommandBase.h>
#include <RestApi/RequestBase.h>
#include <RestApi/RestApiManager.h>

#include <QtCore/QObject>

namespace P1 {
  namespace RestApi {

    RestApiManager* RestApiManager::_commonInstance = nullptr;

    RestApiManager::RestApiManager(QObject *parent /*= 0*/) 
      : QObject(parent)
      , _type(RequestFactory::Http)
      , _cache(nullptr)
      , _uri("https://gnapi.com:8443/restapi") 
      , _debugLogEnabled(false)
    {
    }

    RestApiManager::~RestApiManager()
    {
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

      request->setDebugLogEnabled(this->_debugLogEnabled);

      QObject::connect(request, &RequestBase::finish, command, &CommandBase::resultCallback);

      QObject::connect(command, &CommandBase::genericError,
        this, &RestApiManager::onGenericError, Qt::UniqueConnection);

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

    void RestApiManager::setCridential(const ProtocolOneCredential &credential)
    {
      this->_credential = credential;
    }

    const ProtocolOneCredential &RestApiManager::credential()
    {
      return this->_credential;
    }

    void RestApiManager::setCache(CacheInterface *cache)
    {
      Q_CHECK_PTR(cache);
      this->_cache = cache;
    }

    void RestApiManager::setDebugLogEnabled(bool value)
    {
      this->_debugLogEnabled = value;
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

    void RestApiManager::onGenericError(P1::RestApi::CommandBase::Error error, QString message)
    {
      emit this->genericError(error, message);

      CommandBase *command = qobject_cast<CommandBase*>(QObject::sender());
      if (!command)
        return;

      emit this->genericErrorEx(error, message, command);
    }

  }
}