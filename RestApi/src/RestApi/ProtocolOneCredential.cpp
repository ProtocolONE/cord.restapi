#include <RestApi/ProtocolOneCredential.h>

namespace P1 {
  namespace RestApi {

    ProtocolOneCredential::ProtocolOneCredential()
    {
    }

    ProtocolOneCredential::ProtocolOneCredential(const ProtocolOneCredential &p)
      : _appKey(p._appKey),
        _userId(p._userId),
        _cookie(p._cookie)
    {
    }

    ProtocolOneCredential::~ProtocolOneCredential()
    {
    }

    ProtocolOneCredential & ProtocolOneCredential::operator=(const ProtocolOneCredential &p)
    {
      this->_appKey = p.appKey();
      this->_userId = p.userId();
      this->_cookie = p.cookie();
      return *this;
    }

    bool ProtocolOneCredential::operator==(const ProtocolOneCredential& rhs) const
    {
      return this->_appKey == rhs._appKey
        && this->_userId == rhs._userId
        && this->_cookie == rhs._cookie;
    }

    const QString& ProtocolOneCredential::appKey() const
    {
      return this->_appKey;
    }

    void ProtocolOneCredential::setAppKey(const QString& val)
    {
      this->_appKey = val;
    }

    const QString& ProtocolOneCredential::userId() const
    {
      return this->_userId;
    }

    void ProtocolOneCredential::setUserId(const QString& val)
    {
      this->_userId = val;
    }

    const QString& ProtocolOneCredential::cookie() const
    {
      return this->_cookie;
    }

    void ProtocolOneCredential::setCookie(const QString& val)
    {
      this->_cookie = val;
    }

    bool ProtocolOneCredential::isEmpty() const
    {
      return this->_userId.isEmpty();
    }

  }
}