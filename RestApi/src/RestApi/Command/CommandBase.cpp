#include <RestApi/Command/CommandBase.h>
#include <RestApi/RestApiManager.h>

#include <QtCore/QDebug>
#include <QtCore/QUrlQuery>
#include <QtXml/QDomDocument>

namespace P1 {
  namespace RestApi {
    namespace Command {

      CommandBase::CommandBase(QObject *parent/*=0*/)
        : QObject(parent)
        , _isAuthRequire(false)
        , _isCacheable(true)
        , _statusCode(0)
        , _cacheTime(30)
        , _type(-1)
        , _errorCode(CommandBase::Success)
      {
      }

      CommandBase::~CommandBase()
      {
      }

      bool CommandBase::isAuthRequire()
      {
        return this->_isAuthRequire;
      }

      bool CommandBase::isCacheable()
      {
        return this->_isCacheable;
      }

      int CommandBase::cacheTime()
      {
        return this->_cacheTime;
      }

      void CommandBase::setAuthRequire(bool isAuthRequire)
      {
        this->_isAuthRequire = isAuthRequire;
      }

      void CommandBase::setCacheable(bool isCacheable)
      {
        this->_isCacheable = isCacheable;
      }

      void CommandBase::setCacheTime(int cacheTime)
      {
        this->_cacheTime = cacheTime;
      }

      void CommandBase::setApiUrl(const QString& url)
      {
        this->_apiUrl = url;
      }

      const QString& CommandBase::errorMessage() const
      {
        return this->_errorMessage;
      }

      const int CommandBase::errorCode() const
      {
        return this->_errorCode;
      }

      void CommandBase::setErrorCode(int value)
      {
        this->_errorCode = value;
      }

      bool CommandBase::isSuccess() const
      {
        return this->_errorCode == CommandBase::Success;
      }

      const P1::RestApi::ProtocolOneCredential& CommandBase::credential() const
      {
        return this->_credential;
      }

      void CommandBase::setCredential(const ProtocolOneCredential& value)
      {
        this->_credential = value;
      }

      bool CommandBase::hasCredential() const
      {
        return this->_credential.isEmpty();
      }

      int CommandBase::type() const
      {
        return this->_type;
      }

      void CommandBase::setType(int value)
      {
        this->_type = value;
      }

      int CommandBase::statusCode() const
      {
        return this->_statusCode;
      }

      void CommandBase::setStatusCode(int value)
      {
        this->_statusCode = value;
      }

      void CommandBase::setResponse(const QByteArray& data)
      {

      }

      const QString& CommandBase::apiUrl() const
      {
        return this->_apiUrl;
      }

      const QString& CommandBase::version() const
      {
        return this->_version;
      }

      void CommandBase::setVersion(const QString &version)
      {
        this->_version = version;
      }

      void CommandBase::execute()
      {
        RestApiManager *manager = RestApiManager::commonInstance();
        Q_CHECK_PTR(manager);
        this->execute(manager);
      }

      void CommandBase::execute(RestApiManager *manager)
      {
        manager->execute(this);
      }

      void CommandBase::setError(int statusCode, int commandResult)
      {
        this->_errorCodeMap[statusCode] = commandResult;
      }

      void CommandBase::resultRecevied()
      {
        if (this->_errorCodeMap.contains(this->_statusCode)) {
          this->_errorCode = this->_errorCodeMap[this->_statusCode];
        }

        if (this->_errorCode == CommandBase::Success && this->_statusCode != 200) {
          this->_errorCode = CommandBase::UnknownEror;
        }

        emit this->result();
      }

    }
  }
}