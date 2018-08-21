#include <RestApi/GameNetCredential.h>

namespace P1 {
  namespace RestApi {

    GameNetCredential::GameNetCredential()
    {
    }

    GameNetCredential::GameNetCredential(const GameNetCredential &p)
      : _appKey(p._appKey),
        _userId(p._userId),
        _cookie(p._cookie)
    {
    }

    GameNetCredential::~GameNetCredential()
    {
    }

    GameNetCredential & GameNetCredential::operator=(const GameNetCredential &p)
    {
      this->_appKey = p.appKey();
      this->_userId = p.userId();
      this->_cookie = p.cookie();
      return *this;
    }

    bool GameNetCredential::operator==(const GameNetCredential& rhs) const
    {
      return this->_appKey == rhs._appKey
        && this->_userId == rhs._userId
        && this->_cookie == rhs._cookie;
    }

    const QString& GameNetCredential::appKey() const
    {
      return this->_appKey;
    }

    void GameNetCredential::setAppKey(const QString& val)
    {
      this->_appKey = val;
    }

    const QString& GameNetCredential::userId() const
    {
      return this->_userId;
    }

    void GameNetCredential::setUserId(const QString& val)
    {
      this->_userId = val;
    }

    const QString& GameNetCredential::cookie() const
    {
      return this->_cookie;
    }

    void GameNetCredential::setCookie(const QString& val)
    {
      this->_cookie = val;
    }

    bool GameNetCredential::isEmpty() const
    {
      return this->_userId.isEmpty();
    }

  }
}