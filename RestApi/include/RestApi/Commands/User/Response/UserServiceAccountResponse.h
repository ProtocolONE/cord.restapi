#pragma once

#include <RestApi/restapi_global.h>

#include <QObject>
#include <QString>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace User {
        namespace Response {

          class RESTAPI_EXPORT UserServiceAccountResponse: public QObject
          {
              Q_OBJECT
		      public:
            void setLogin(const QString login);
            const QString getLogin();

            void setPassword(const QString password);
            const QString getPassword();

            void setToken(const QString token);
            const QString getToken();

            void setStatus(const QString status);
            const QString getStatus();

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
