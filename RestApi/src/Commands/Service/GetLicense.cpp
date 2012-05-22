#include <RestApi/Commands/Service/GetLicense.h>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Service {

        GetLicense::GetLicense(const QString& serviceId)
          : _isLicenseNew(false)
        {
          this->appendParameter("method", "service.getLicense");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "qgna_ru");
          this->appendParameter("serviceId", serviceId);
          this->_serviceId = serviceId;
        }

        GetLicense::~GetLicense()
        {

        }

        void GetLicense::setHash(const QString& hash)
        {
          this->appendParameter("hash", hash);
        }

        bool GetLicense::callMethod(const QDomDocument& response)
        {
          QDomElement responseElement = response.documentElement();
          QDomElement licenseElement = responseElement.firstChildElement("license");
          QDomElement textDom = licenseElement.firstChildElement("text");
          QDomElement isNewDom = licenseElement.firstChildElement("isnew");
          QDomElement hashDom = licenseElement.firstChildElement("hash");
          if (textDom.isNull() || isNewDom.isNull() || hashDom.isNull())
            return true;

          this->_licenseText = textDom.text();
          this->_responseHash = hashDom.text();
          this->_isLicenseNew = isNewDom.text() == "1";
          return false;
        }

        const QString& GetLicense::responseHash()
        {
          return this->_responseHash;
        }

        const QString& GetLicense::licenseText()
        {
          return this->_licenseText;
        }

        bool GetLicense::isLicenseNew()
        {
          return this->_isLicenseNew;
        }

        const QString& GetLicense::serviceId() const
        {
          return this->_serviceId;
        }

      }
    }
  }
}