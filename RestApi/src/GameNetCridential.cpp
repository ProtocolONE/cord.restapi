/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "GameNetCredential.h"

namespace GGS {
  namespace RestApi {

    GameNetCredential::GameNetCredential(){
    }

    GameNetCredential::GameNetCredential( const GameNetCredential &p )
      : _appKey(p._appKey),
        _userId(p._userId),
        _cookie(p._cookie)
    {
    }


    GameNetCredential::~GameNetCredential()
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