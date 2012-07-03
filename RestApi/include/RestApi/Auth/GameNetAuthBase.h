/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_AUTH_GAMENET_AUTHINTERFACE_H_
#define _GGS_RESTAPI_AUTH_GAMENET_AUTHINTERFACE_H_

#include <RestApi/restapi_global.h>
#include <RestApi/GameNetCredential.h>

#include <QtCore/QString>
#include <QtCore/QObject>
#include <QtCore/QMetaType>

namespace GGS {
  namespace RestApi {
    namespace Auth {

      class RESTAPI_EXPORT GameNetAuthBase : public QObject
      {
        Q_OBJECT
        Q_ENUMS(GGS::RestApi::Auth::GameNetAuthBase::AuthResultCodes);
      public:
        enum AuthResultCodes {
          Success = 0, // Без ошибок прошла
          UnknownError = 1,
          Cancel = 2, // Например в случаи закрытия окна вконтакта - можно не показывать ошибку.
          NetworkError = 3,
          WrongLoginOrPassword = 4, 
          UnknownAuthMethod = 5,
          ServiceAccountBlocked = 6,
        };

        GameNetAuthBase(QObject *parent = 0);
        virtual ~GameNetAuthBase();

        virtual const QString& type() = 0;
        virtual void login() = 0;

      signals:
        void authResult(const GGS::RestApi::GameNetCredential cridential);
        void authFailed(GGS::RestApi::Auth::GameNetAuthBase::AuthResultCodes resultCode);
      };
    }
  }
}

Q_DECLARE_METATYPE(GGS::RestApi::Auth::GameNetAuthBase::AuthResultCodes);

#endif // _GGS_RESTAPI_AUTH_GAMENET_AUTHINTERFACE_H_