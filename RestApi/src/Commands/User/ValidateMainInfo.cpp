#include <Commands/User/ValidateMainInfo.h>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        ValidateMainInfo::ValidateMainInfo(QObject *parent)
          : CommandBase(parent)
        {
          this->appendParameter("method", "user.validateMainInfo");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
        }

        ValidateMainInfo::~ValidateMainInfo()
        {
        }

        bool ValidateMainInfo::callMethod(const QDomDocument& response)
        {
          QDomElement responseElement = response.documentElement();

          if(responseElement.isNull())
            return true;

          QDomElement el = responseElement.firstChildElement("result");
          if(!el.isNull() && 1 == el.text().toInt()) 
            return false;

          return true;
        }

        void ValidateMainInfo::setFieldValue(const QString &field, const QString &value)
        {
          this->appendParameter(field, value);
        }
      }
    }
  }
}
