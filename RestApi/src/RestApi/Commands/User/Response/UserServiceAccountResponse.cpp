#include <RestApi/Commands/User/Response/UserServiceAccountResponse.h>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace User {
        namespace Response {

          void UserServiceAccountResponse::setLogin(const QString login)
          {
            this->_login = login;
          }

          const QString UserServiceAccountResponse::getLogin()
          {
            return this->_login;
          }

          void UserServiceAccountResponse::setPassword(const QString password)
          {
            this->_password = password;
          }

          const QString UserServiceAccountResponse::getPassword()
          {
            return this->_password;
          }

          void UserServiceAccountResponse::setToken(const QString token)
          {
            this->_token = token;
          }

          const QString UserServiceAccountResponse::getToken()
          {
            return this->_token;
          }

          void UserServiceAccountResponse::setStatus(const QString status)
          {
            this->_status = status;
          }

          const QString UserServiceAccountResponse::getStatus()
          {
            return this->_status;
          }

        }
      }
    }
  }
}
