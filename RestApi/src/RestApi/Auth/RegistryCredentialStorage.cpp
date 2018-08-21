#include <RestApi/Auth/RegistryCredentialStorage.h>
#include <QtCore/QCryptographicHash>

namespace P1 {
  namespace RestApi {
    namespace Auth {

      RegistryCredentialStorage::RegistryCredentialStorage()
        : _path("HKEY_CURRENT_USER\\Software\\Pone\\QGNA\\")
      {
        this->_settings = new QSettings(this->_path, QSettings::NativeFormat);
      }

      RegistryCredentialStorage::RegistryCredentialStorage(const QString &path)
      {
        this->_path = path;
        this->_settings = new QSettings(this->_path, QSettings::NativeFormat);
      }
      
      RegistryCredentialStorage::~RegistryCredentialStorage()
      {
        if (this->_settings) 
          delete this->_settings;
      }

      const QString RegistryCredentialStorage::calcHash(const GameNetCredential& credential)
      {
        QCryptographicHash hash(QCryptographicHash::Sha1);
        hash.addData(credential.userId().toLatin1());
        hash.addData(credential.appKey().toLatin1());
        hash.addData(credential.cookie().toLatin1());

        return QString(hash.result().toHex());
      }

      void RegistryCredentialStorage::save(const GameNetCredential& credential)
      {
        //ВАЖНО! Код сохраняющий данные в реестр и вычисляющий CRC нельзя
        //менять не исправляя синхронно код gnalogin/getCredential который нужен
        //для работы фичи "авторизация из инсталлятора" 
        this->_settings->setValue("userId", credential.userId());
        this->_settings->setValue("appKey", credential.appKey());
        this->_settings->setValue("cookie", credential.cookie());
        this->_settings->setValue("crc", this->calcHash(credential));
      }

      bool RegistryCredentialStorage::tryLoad(GameNetCredential& credential)
      {
        if (!this->_settings->contains("userId")
          || !this->_settings->contains("appKey")
          || !this->_settings->contains("cookie")
          || !this->_settings->contains("crc"))
        {
           this->reset();
           return false;
        }

        GameNetCredential savedCredential;
        savedCredential.setUserId(this->_settings->value("userId").toString());
        savedCredential.setAppKey(this->_settings->value("appKey").toString());
        savedCredential.setCookie(this->_settings->value("cookie").toString());

        QString savedCrc = this->_settings->value("crc").toString();
        if (savedCrc != this->calcHash(savedCredential)) {
          this->reset();
          return false;
        }
       
        credential = savedCredential;
        return true;
      }

      void RegistryCredentialStorage::reset()
      {
        this->_settings->remove("userId");
        this->_settings->remove("appKey");
        this->_settings->remove("cookie");
        this->_settings->remove("crc");
      }
    }
  }
}