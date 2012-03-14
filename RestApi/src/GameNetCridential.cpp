#include "GameNetCredential.h"

namespace GGS {
  namespace RestApi {

    GameNetCredential::GameNetCredential(void)
    {
    }

    GameNetCredential::GameNetCredential( const GameNetCredential &p )
      : _appKey(p._appKey),
        _userId(p._userId),
        _cookie(p._cookie)
    {
    }


    GameNetCredential::~GameNetCredential(void)
    {
    }

    GameNetCredential & GameNetCredential::operator=( const GameNetCredential &p )
    {
      this->_appKey = p.appKey();
      this->_userId = p.userId();
      this->_cookie = p.cookie();
      return *this;
    }

  }
}