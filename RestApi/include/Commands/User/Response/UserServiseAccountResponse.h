#ifndef _GGS_RESTAPI_COMMANDS_USER_RESPONSE_USERSERVISEACCOUNTRESPONSE_H_
#define _GGS_RESTAPI_COMMANDS_USER_RESPONSE_USERSERVISEACCOUNTRESPONSE_H_

#include "restapi_global.h"
#include <QtCore/QObject>
#include <QtCore/QString>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {
        namespace Response {

          class RESTAPI_EXPORT UserServiseAccountResponse : public QObject
          {
            Q_OBJECT
          public:
            UserServiseAccountResponse();
            ~UserServiseAccountResponse();

            void setLogin(const QString& login) { _login = login; }
            const QString& getLogin() { return _login; }

            void setPassword(const QString& password) { _password = password; }
            const QString& getPassword() { return _password; }

            void setToken(const QString& token) { _token = token; }
            const QString& getToken() { return _token; }

            void setStatus(const QString& status) { _status = status; }
            const QString& getStatus() { return _status; }

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