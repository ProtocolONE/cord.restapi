#pragma once

#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QHash>

namespace P1 {
  namespace RestApi {

    namespace Request {
      class RequestBase;
    }

    namespace Command {
      class CommandBase;
    }

    class RefreshTokenState;
    class ProtocolOneCredential;

    class RefreshTokenManager : public QObject
    {
      Q_OBJECT
    public:
      explicit RefreshTokenManager(QObject *parent = 0);
      virtual ~RefreshTokenManager() = default;
      
      void refreshToken(Request::RequestBase *sender, const ProtocolOneCredential &credential);
      void updateCredential(const ProtocolOneCredential &old, const ProtocolOneCredential &value);

    signals:
      void refreshTokenRequest(const ProtocolOneCredential &credential, const Command::CommandBase* command);

    private:
      QMutex _mutex;
      QHash<QString, RefreshTokenState*> _states;
    };

  }
}