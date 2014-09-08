/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <RestApi/Commands/Marketing/SetGnaInstallStep.h>

namespace GGS {
    namespace RestApi {
        namespace Commands {
            namespace Marketing {
              SetGnaInstallStep::SetGnaInstallStep()
              {
                  this->appendParameter("method", "marketing.setGnaInstallStep");
                  this->appendParameter("version", "1");
                  this->appendParameter("lang", "ru");
                  this->setAuthRequire(false);
                  this->_ok = false;
              }

              SetGnaInstallStep::~SetGnaInstallStep()
              {
              }

              void SetGnaInstallStep::setHwid(const QString& hwid)
              {
                  this->appendParameter("hwid", hwid);
              }

              void SetGnaInstallStep::setServiceId(const QString& serviceId)
              {
                  this->appendParameter("serviceId", serviceId);
              }

              void SetGnaInstallStep::setMarketingTarget(int marketingTarget)
              {
                  this->appendParameter("marketModuleTarget", QString::number(marketingTarget));
              }

              void SetGnaInstallStep::setMarketingId(const QString& mid)
              {
                this->appendParameter("marketingId", mid);
              }

              void SetGnaInstallStep::setParamsMap(const QVariantMap& params)
              {
                if (params.count() > 0) {
                  QString result("<params>");
                  QVariantMap::const_iterator end = params.constEnd();
                  for (QVariantMap::const_iterator it = params.constBegin(); it != end; ++it)
                    result.append(QString("<param><name>%1</name><value>%2</value></param>").arg(it.key(), it.value().toString()));

                  result.append("</params>");
                  this->appendParameter("params", result);
                }
              }

              void SetGnaInstallStep::setUserId(const QString& userId)
              {
                this->appendParameter("userId", userId);
              }

              void SetGnaInstallStep::setAppKey(const QString& appKey)
              {
                this->appendParameter("appKey", appKey);
              }

              bool SetGnaInstallStep::callMethod(const QDomDocument& response)
              {
                QDomElement el = response.documentElement().firstChildElement("status");

                if(!el.isNull()) {
                  this->_ok = el.text() == "ok";
                  return false;
                } 

                return true;
              }

              bool SetGnaInstallStep::isSuccess()
              {
                return _ok;
              }
            }
        }
    }
}