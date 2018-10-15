#pragma once

#include <QtCore/QObject>

#include <RestApi/ProtocolOneCredential.h>

namespace P1 {
  namespace RestApi {

    class RefreshTokenState : public QObject
    {
      Q_OBJECT
    public:
      explicit RefreshTokenState(QObject* parent = 0);
      virtual ~RefreshTokenState() = default;

      void setCredential(const ProtocolOneCredential& credential);

    signals:
      void credentialReceived(const ProtocolOneCredential& credential);
    };

  }
}