#include <RestApi/ProtocolOneCredential.h>
#include <QtCore/QStringList>
#include <QtCore/QDebug>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

namespace P1 {
  namespace RestApi {

    ProtocolOneCredential::ProtocolOneCredential()
    {
    }

    ProtocolOneCredential::ProtocolOneCredential(
      const QString& acccessTokent, const QDateTime& accessTokenExpiredTime, QObject *parent)
      : _acccessTokent(acccessTokent)
      , _accessTokenExpiredTime(accessTokenExpiredTime)
    {
      this->parseToken();
    }

    bool ProtocolOneCredential::operator==(const ProtocolOneCredential& other) const
    {
      return this->_acccessTokent == other._acccessTokent
        && this->_accessTokenExpiredTime == other._accessTokenExpiredTime;
    }

    bool ProtocolOneCredential::operator!=(const ProtocolOneCredential& other) const
    {
      return !(*this == other);
    }

    ProtocolOneCredential::~ProtocolOneCredential()
    {
    }

    void ProtocolOneCredential::clear()
    {
      this->_userId.clear();
      this->_acccessTokent.clear();
      this->_accessTokenExpiredTime = QDateTime::currentDateTime().addSecs(-1);
    }

    ProtocolOneCredential& ProtocolOneCredential::operator=(const ProtocolOneCredential &p)
    {
      this->_acccessTokent = p._acccessTokent;
      this->_accessTokenExpiredTime = p._accessTokenExpiredTime;

      this->parseToken();
      return *this;
    }

    bool ProtocolOneCredential::isEmpty() const
    {
      return this->_acccessTokent.isEmpty();
    }

    bool ProtocolOneCredential::isValid() const
    {
      return !this->_acccessTokent.isEmpty() && QDateTime::currentDateTimeUtc() < this->_accessTokenExpiredTime;
    }

    const QString& ProtocolOneCredential::acccessTokent() const
    {
      return this->_acccessTokent;
    }

    void ProtocolOneCredential::setAcccessTokent(const QString& val)
    {
      this->_acccessTokent = val;
      this->parseToken();
    }

    const QDateTime& ProtocolOneCredential::accessTokenExpiredTime() const
    {
      return this->_accessTokenExpiredTime;
    }

    void ProtocolOneCredential::setAccessTokenExpiredTime(const QDateTime& val)
    {
      this->_accessTokenExpiredTime = val;
    }

    const QString& ProtocolOneCredential::userId() const
    {
      return this->_userId;
    }

    void ProtocolOneCredential::parseToken()
    {
      this->_userId.clear();
      if (this->_acccessTokent.isEmpty())
        return;

      QStringList tokens = this->_acccessTokent.split('.');
      if (tokens.length() != 3)
        return;

      QJsonParseError jsonError;
      QJsonDocument doc = QJsonDocument::fromJson(QByteArray::fromBase64(tokens[1].toLatin1()), &jsonError);
      if (jsonError.error != QJsonParseError::NoError) {
        WARNING_LOG << jsonError.errorString();
        return;
      }

      QJsonObject root = doc.object();
      QJsonValue userId = root["id"];
      this->_userId = userId.toString();
    }

  }
}