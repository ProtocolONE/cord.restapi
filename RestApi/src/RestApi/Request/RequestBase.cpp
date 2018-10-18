#include <RestApi/Request/RequestBase.h>
#include <RestApi/Command/CommandBase.h>

#include <stdint.h>

const int32_t Uninitialized = -1;
const int32_t NoAuth = 1;
const int32_t Initialized = 2;
const int32_t WaitForRefresh = 3;

using P1::RestApi::Command::CommandBase;

namespace P1 {
  namespace RestApi {

    namespace Request {
      RequestBase::RequestBase(QObject *parent /*= 0*/)
        : QObject(parent)
        , _debugLogEnabled(false)
        , _status(Uninitialized)
        , _cache(nullptr)
        , _command(nullptr)
      {
      }

      RequestBase::~RequestBase()
      {
      }

      const P1::RestApi::Command::CommandBase * RequestBase::command() const
      {
        return this->_command;
      }

      void RequestBase::setCommand(CommandBase *command)
      {
        Q_CHECK_PTR(command);
        this->_command = command;
      }

      void RequestBase::setCache(CacheInterface *cache)
      {
        this->_cache = cache;
      }

      void RequestBase::setDebugLogEnabled(bool value)
      {
        this->_debugLogEnabled = value;
      }

      void RequestBase::execute()
      {
        Q_CHECK_PTR(this->_command);

        if (!this->_command->isAuthRequire()) {
          this->_status = NoAuth;
          this->internalExecute();
          return;
        }

        if (this->_command->credential().isValid()) {
          this->_status = Initialized;
          this->internalExecute();
          return;
        }

        this->_status = WaitForRefresh;
        emit this->refreshAuth(this->_command->credential());
      }

      void RequestBase::updateCredential(const ProtocolOneCredential& credential)
      {
        // check for right credential?
        this->_command->setCredential(credential);

        if (!credential.isValid()) {
          this->_command->setErrorCode(CommandBase::Unauthorized);
          this->_command->resultRecevied();
          return;
        }

        this->internalExecute();
      }

      void RequestBase::resultReceived()
      {
        if (this->_status == Initialized) {
          if (this->_command->statusCode() == 401) {
            // Initialized and need auth. So we should refresh auth and retry command.
            this->_status = WaitForRefresh;
            emit this->refreshAuth(this->_command->credential());
            return;
          }
        }

        if (this->_command->statusCode() == 401) {
          this->_command->setErrorCode(CommandBase::Unauthorized);
        }

        this->_command->resultRecevied();
      }

    }
  }
}