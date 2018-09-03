#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/ProtocolOneCredential.h>
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

        virtual void save(const ProtocolOneCredential& credential);

        virtual bool tryLoad(ProtocolOneCredential& credential);

        virtual void reset();
      private:
        const QString calcHash(const ProtocolOneCredential& credential);
        QString _path;
        QPointer<QSettings> _settings;
      };
    }
  }
}
