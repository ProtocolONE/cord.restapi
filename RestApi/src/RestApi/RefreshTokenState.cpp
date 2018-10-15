#include <RestApi/RefreshTokenState.h>

namespace P1 {
  namespace RestApi {

    RefreshTokenState::RefreshTokenState(QObject* parent /*= 0*/)
      : QObject(parent)
    {

    }

    void RefreshTokenState::setCredential(const ProtocolOneCredential& credential)
    {
      emit this->credentialReceived(credential);
    }

  }
}