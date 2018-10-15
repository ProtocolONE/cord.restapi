#include <RestApi/RestApiManager.h>

#include <RestApi/Command/CommandBase.h>

#include <RestApi/Request/RequestBase.h>

#include <QtCore/QObject>
#include <QtCore/QTimer>

using P1::RestApi::Command::CommandBase;

namespace P1 {
  namespace RestApi {

    using Request::RequestBase;

    RestApiManager* RestApiManager::_commonInstance = nullptr;

    RestApiManager::RestApiManager(QObject *parent /*= 0*/) 
      : QObject(parent)
      , _cache(nullptr)
      , _debugLogEnabled(false)
    {
    }

    RestApiManager::~RestApiManager()
    {
    }

    void RestApiManager::execute(CommandBase *command)
    {
      Q_CHECK_PTR(command);

      if (command->isAuthRequire() && !command->hasCredential())
        command->setCredential(this->_credential);

      if (command->apiUrl().isEmpty())
        command->setApiUrl(this->_uri);

      RequestBase *request = this->_factory.create(command->type());
      if (this->_cache) 
        request->setCache(this->_cache);

      request->setDebugLogEnabled(this->_debugLogEnabled);
      request->setCommand(command);

      QObject::connect(request, &RequestBase::refreshAuth, this, &RestApiManager::onRefreshTokentRequest);

      QObject::connect(command, &CommandBase::result,
        this, &RestApiManager::onCommandResult, Qt::UniqueConnection);

      QTimer::singleShot(0, request, &RequestBase::execute);
    }

    void RestApiManager::setUri(const QString& uri)
    {
      this->_uri = uri;
    }

    void RestApiManager::setCridential(const ProtocolOneCredential &credential)
    {
      this->_credential = credential;
    }

    const ProtocolOneCredential &RestApiManager::credential()
    {
      return this->_credential;
    }

    void RestApiManager::updateCredential(const ProtocolOneCredential &old, const ProtocolOneCredential &value)
    {
      this->_refreshManger.updateCredential(old, value);
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

    void RestApiManager::onCommandResult()
    {
      CommandBase *command = qobject_cast<CommandBase*>(QObject::sender());
      if (!command)
        return;

      if (command->errorCode() == CommandBase::Unauthorized) {
        const ProtocolOneCredential& credential(command->credential());

        if (!credential.isEmpty())
          emit this->authorizationError(credential, command);
      }
    }

    void RestApiManager::onRefreshTokentRequest(const ProtocolOneCredential& value)
    {
      RequestBase *cmd = qobject_cast<RequestBase *>(QObject::sender());
      this->_refreshManger.refreshToken(cmd, value);
    }

  }
}