/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <RestApi/Commands/Marketing/InstallerStep.h>

#include <QtCore/QCryptographicHash>
#include <QtCore/QByteArray>

#define SECRET_KEY "1super_secret_key1"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Marketing {

        InstallerStep::InstallerStep(QObject *parent)
          : CommandBase(parent)
          , _ok(false)
        {
          this->appendParameter("method", "marketing.setInstallerStep");
          this->setAuthRequire(false);
        }

        InstallerStep::~InstallerStep()
        {
        }

        void InstallerStep::setHwid(const QString& hwid)
        {
          QByteArray buffer(hwid.toUtf8());
          QString encodedHwid(buffer.toBase64());
          this->_hwid = encodedHwid;
        }

        void InstallerStep::setInstallerKey(int key)
        {
          this->_installerKey = key;
        }

        void InstallerStep::setMarketingId(const QString& mid)
        {
          this->_mid = mid;
        }

        void InstallerStep::setStep(int step)
        {
          this->_step = step;
        }

        void InstallerStep::setCustomParams(const QVariantMap& params)
        {
          if (params.count() <= 0)
            return;

          QString result("<params>");
          QVariantMap::const_iterator end = params.constEnd();
          for (QVariantMap::const_iterator it = params.constBegin(); it != end; ++it)
            result.append(QString("<param><name>%1</name><value>%2</value></param>").arg(it.key(), it.value().toString()));

          this->_customParams = result;
        }

        void InstallerStep::sign()
        {
          QString checksum;

          this->appendParameter("instKey", QString::number(this->_installerKey));
          checksum.append(QString::number(this->_installerKey));

          this->appendParameter("hwid", this->_hwid);
          checksum.append(this->_hwid);

          this->appendParameter("marketingId", this->_mid);
          checksum.append(this->_mid);

          this->appendParameter("step", QString::number(this->_step));
          checksum.append(QString::number(this->_step));

          if (this->_customParams.size() > 0) {
            this->appendParameter("params", this->_customParams);
            checksum.append(this->_customParams);
          }

          checksum.append(SECRET_KEY);

          QString checksumHash(QCryptographicHash::hash(checksum.toUtf8(), QCryptographicHash::Md5).toHex());
          this->appendParameter("sum", checksumHash);
        }

        bool InstallerStep::callMethod(const QDomDocument& response)
        {
          QDomElement el = response.documentElement().firstChildElement("status");

          if(!el.isNull()) {
            this->_ok = el.text() == "ok";
            return false;
          } 

          return true;
        }

        bool InstallerStep::isSuccess()
        {
          return _ok;
        }

      }
    }
  }
}