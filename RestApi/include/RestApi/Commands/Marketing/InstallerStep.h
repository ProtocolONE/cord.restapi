#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtCore/QVariantMap>
#include <QtXml/QDomDocument>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace Marketing {

        class RESTAPI_EXPORT InstallerStep : public CommandBase
        {
          Q_OBJECT
        public:
          InstallerStep(QObject *parent = 0);
          ~InstallerStep();

          virtual bool callMethod(const QDomDocument& response);
          bool isSuccess();

          void setHwid(const QString& hwid);
          void setMarketingId(const QString& mid);
          void setInstallerKey(int key);
          void setStep(int step);
          void setCustomParams(const QVariantMap& params);

          void sign();

        private:
          bool _ok;

          int _installerKey;
          QString _hwid;
          QString _mid;
          int _step;
          QString _customParams;

        };

      }
    }
  }
}
