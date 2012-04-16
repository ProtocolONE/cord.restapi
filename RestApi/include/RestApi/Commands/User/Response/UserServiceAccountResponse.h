/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDS_USER_RESPONSE_USERSERVICEACCOUNTRESPONSE_H_
#define _GGS_RESTAPI_COMMANDS_USER_RESPONSE_USERSERVICEACCOUNTRESPONSE_H_

#include <RestApi/restapi_global.h>

#include <QObject>
#include <QString>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {
        namespace Response {

          class RESTAPI_EXPORT UserServiceAccountResponse
          {

		  public:
            void setLogin(const QString login) { this->_login = login; }
            const QString getLogin() { return this->_login; }

            void setPassword(const QString password) { this->_password = password; }
            const QString getPassword() { return this->_password; }

            void setToken(const QString token) { this->_token = token; }
            const QString getToken() { return this->_token; }

            void setStatus(const QString status) { this->_status = status; }
            const QString getStatus() { return this->_status; }

          private:
            QString _login;
            QString _password;
            QString _token;
            QString _status;
          };
        }
      }
    }
  }
}

#endif