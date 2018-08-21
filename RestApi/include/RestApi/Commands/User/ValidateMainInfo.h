#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>
#include <RestApi/Commands/User/Response/UserServiceAccountResponse.h>

#include <QtCore/QPointer>
#include <QtXml/QDomDocument>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace User {

        class RESTAPI_EXPORT ValidateMainInfo : public CommandBase
        {
          Q_OBJECT
        public:
          explicit ValidateMainInfo(QObject *parent = 0);
          ~ValidateMainInfo();
          
          void setFieldValue(const QString &field, const QString &value);

          virtual bool callMethod(const QDomDocument& response);
        };
      }
    }
  }
}
