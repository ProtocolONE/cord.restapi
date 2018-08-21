#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/GameNetCredential.h>
#include <RestApi/Auth/CredentialStorageInterface.h>

#include <QtCore/QString>
#include <QtCore/QSettings>
#include <QtCore/QPointer>


namespace P1 {
  namespace RestApi {
    namespace Auth {

      class RESTAPI_EXPORT RegistryCredentialStorage : 
        public QObject, 
        public P1::RestApi::Auth::CredentialStorageInterface
      {
        Q_OBJECT
      public:
        RegistryCredentialStorage();
        RegistryCredentialStorage(const QString &path);
        virtual ~RegistryCredentialStorage();

        virtual void save(const GameNetCredential& credential);

        virtual bool tryLoad(GameNetCredential& credential);

        virtual void reset();
      private:
        const QString calcHash(const GameNetCredential& credential);
        QString _path;
        QPointer<QSettings> _settings;
      };
    }
  }
}
