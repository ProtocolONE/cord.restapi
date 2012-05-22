#ifndef _GGS_RESTAPI_COMMANDS_SERVICE_GETLICENSE_H_
#define _GGS_RESTAPI_COMMANDS_SERVICE_GETLICENSE_H_

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Service {
        class RESTAPI_EXPORT GetLicense : public CommandBase 
        {
          Q_OBJECT
        public:
          GetLicense(const QString& serviceId);
          ~GetLicense();

          const QString& serviceId() const;
          void setHash(const QString& hash);

          virtual bool callMethod(const QDomDocument& response);

          const QString& responseHash();
          const QString& licenseText();          
          bool isLicenseNew();

        private:
           QString _responseHash;
           QString _licenseText;
           bool _isLicenseNew;
           QString _serviceId;
        };

      }
    }
  }
}
#endif // _GGS_RESTAPI_COMMANDS_SERVICE_GETLICENSE_H_