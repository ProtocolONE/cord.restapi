#include <RestApi/RefreshTokenManager.h>

#include <RestApi/RefreshTokenState.h>
#include <RestApi/ProtocolOneCredential.h>

#include <RestApi/Request/RequestBase.h>
#include <RestApi/Command/CommandBase.h>

#include <QtCore/QMutexLocker>

namespace P1 {
  namespace RestApi {

    RefreshTokenManager::RefreshTokenManager(QObject *parent /*= 0*/)
      : QObject(parent)
    {

    }

    void RefreshTokenManager::refreshToken(Request::RequestBase *sender, const ProtocolOneCredential &credential)
    {
      if (credential.isEmpty())
        return;

      QMutexLocker lock(&this->_mutex);

      RefreshTokenState *state = nullptr;
      if (this->_states.contains(credential.acccessTokent())) {
        state = this->_states[credential.acccessTokent()];
        QObject::connect(state, &RefreshTokenState::credentialReceived, 
          sender, &Request::RequestBase::updateCredential, Qt::QueuedConnection);
        return;
      } 
        
      state = new RefreshTokenState(this);
      this->_states[credential.acccessTokent()] = state;

      QObject::connect(state, &RefreshTokenState::credentialReceived, 
        sender, &Request::RequestBase::updateCredential, Qt::QueuedConnection);

      this->refreshTokenRequest(credential, sender->command());
    }

    void RefreshTokenManager::updateCredential(const ProtocolOneCredential &old, const ProtocolOneCredential &value)
    {
      QMutexLocker lock(&this->_mutex);
      if (!this->_states.contains(old.acccessTokent()))
        return;

      const QString& acccessTokent(old.acccessTokent());
      RefreshTokenState *state = this->_states[acccessTokent];
      state->setCredential(value);

      this->_states.remove(acccessTokent);

      state->deleteLater();
    }

  }
}