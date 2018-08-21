
#include <RestApi/Auth/GetRedirectToken.h>

namespace P1 {
  namespace RestApi {
    namespace Auth {

      GetRedirectToken::GetRedirectToken(QObject *parent) : CommandBase(parent)
      {
        this->appendParameter("method", "auth.getRedirectToken");
        this->appendParameter("version", "1");
        this->appendParameter("lang", "ru");
        this->setAuthRequire(true);
      }

      GetRedirectToken::~GetRedirectToken()
      {
      }

      bool GetRedirectToken::callMethod(const QDomDocument& response)
      {
        QDomElement responseElement = response.documentElement();
        QDomElement token = responseElement.firstChildElement("token");

        if (token.isNull() || token.text().isEmpty())
          return true;

        this->_token = token.text();
        return false;
      }

      const QString& GetRedirectToken::token() const
      {
        return this->_token;
      }
    }
  }
}
