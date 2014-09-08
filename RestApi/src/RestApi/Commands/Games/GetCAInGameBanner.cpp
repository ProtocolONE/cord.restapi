#include <RestApi/Commands/Games/GetCAInGameBanner.h>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Games {

        GetCAInGameBanner::GetCAInGameBanner(QObject *parent /*= 0*/)
          : CommandBase(parent)
        {
          this->appendParameter("method", "games.getCAInGameBanner");
          this->appendParameter("version", "2");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(false);
        }

        GetCAInGameBanner::~GetCAInGameBanner()
        {
        }

        bool GetCAInGameBanner::callMethod(const QDomDocument& response)
        {
           QDomElement imageElement = response.documentElement()
             .firstChildElement("banner")
             .firstChildElement("image");

           if (imageElement.isNull())
             return true;

           this->_imageUrl = imageElement.text();
           return false;
        }

        const QString& GetCAInGameBanner::imageUrl()
        {
          return this->_imageUrl;
        }

      }
    }
  }
}