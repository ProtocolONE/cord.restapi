#pragma once

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QHash>

#include <RestApi/ProtocolOneCredential.h>
#include <RestApi/RefreshTokenState.h>
#include <RestApi/Request/RequestBase.h>

namespace P1 {
  namespace RestApi {

    class RefreshTokenManager : public QObject
    {
      Q_OBJECT
    public:
      explicit RefreshTokenManager(QObject *parent = 0);
      virtual ~RefreshTokenManager() = default;
      
      void refreshToken(Request::RequestBase *sender, const ProtocolOneCredential &credential);
      void updateCredential(const ProtocolOneCredential &old, const ProtocolOneCredential &value);

    signals:
      void refreshTokenRequest(const ProtocolOneCredential &credential);

    private:
      QMutex _mutex;
      QHash<QString, RefreshTokenState*> _states;
    };

  }
}