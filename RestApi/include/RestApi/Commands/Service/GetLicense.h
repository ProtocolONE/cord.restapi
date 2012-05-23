/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

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