#include <RestApi/RefreshTokenManager.h>
#include <RestApi/Request/RequestBase.h>
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
        QObject::connect(state, &RefreshTokenState::credentialReceived, sender, &Request::RequestBase::updateCredential);
        return;
      } 
        
      state = new RefreshTokenState(this);
      this->_states[credential.acccessTokent()] = state;

      QObject::connect(state, &RefreshTokenState::credentialReceived, sender, &Request::RequestBase::updateCredential);
      this->refreshTokenRequest(credential);
    }

    void RefreshTokenManager::updateCredential(const ProtocolOneCredential &old, const ProtocolOneCredential &value)
    {
      QMutexLocker lock(&this->_mutex);
      if (!this->_states.contains(old.acccessTokent()))
        return;

      RefreshTokenState *state = this->_states[old.acccessTokent()];
      state->setCredential(value);
    }

  }
}