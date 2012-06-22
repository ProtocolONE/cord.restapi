#include <Commands/User/SaveMainInfo.h>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        SaveMainInfo::SaveMainInfo(QObject *parent)
          : CommandBase(parent)
        {
          this->appendParameter("method", "user.saveMainInfo");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);
        }

        SaveMainInfo::~SaveMainInfo()
        {
        }

        bool SaveMainInfo::callMethod(const QDomDocument& response)
        {
          QDomElement responseElement = response.documentElement();

          if(responseElement.isNull())
            return true;

          QDomElement el = responseElement.firstChildElement("result");
          if(!el.isNull() && 1 == el.text().toInt()) 
            return false;

          return true;
        }

        void SaveMainInfo::setFieldValue( const QString &field, const QString &value )
        {
          this->appendParameter(field, value);
        }
      }
    }
  }
}
