/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#include <RestApi/Commands/Service/GetHosts.h>
#include <QDebug>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Service {

        GetHosts::GetHosts(QObject* parent) : CommandBase(parent)
        {
          this->appendParameter("method", "service.getHosts");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(false);
        }

        GetHosts::~GetHosts()
        {
        }

        bool GetHosts::callMethod(const QDomDocument& response)
        {
          QDomElement responseElement = response.documentElement();
          QDomElement row = responseElement.firstChildElement("row");

          for (; !row.isNull(); row = row.nextSiblingElement("row")) {
            QDomElement serviceIdElement = row.firstChildElement("serviceId");
            QDomElement gameIdElement = row.firstChildElement("gameId");
            QDomElement folderNameElement = row.firstChildElement("folderName");
            QDomElement torrentUrlElement = row.firstChildElement("torrentUrl");
            QDomElement hasDownloadPathElement = row.firstChildElement("hasDownloadPath");
            QDomElement isBrowserGameElement = row.firstChildElement("isBrowserGame");
            QDomElement extractorTypeElement = row.firstChildElement("extractorType");
            QDomElement executeUrlElement = row.firstChildElement("executeUrl");
            QDomElement dependencyListElement = row.firstChildElement("dependencyList");
            QDomElement gameSizeElement = row.firstChildElement("gameSize");
            QDomElement downloadHooksElement = row.firstChildElement("downloadHooks");
            QDomElement executorHooksElement = row.firstChildElement("executorHooks");
            QDomElement isPublishedInAppElement = row.firstChildElement("isPublishedInApp");
            QDomElement iconInAppElement = row.firstChildElement("iconInApp");

            QMap<QString, QString> serviceMap;
            serviceMap["serviceId"] = serviceIdElement.text();
            serviceMap["gameId"] = gameIdElement.text();
            serviceMap["folderName"] = folderNameElement.text();
            serviceMap["torrentUrl"] = torrentUrlElement.text();
            serviceMap["hasDownloadPath"] = hasDownloadPathElement.text();
            serviceMap["isBrowserGame"] = isBrowserGameElement.text();
            serviceMap["extractorType"] = extractorTypeElement.text();
            serviceMap["executeUrl"] = executeUrlElement.text();
            serviceMap["dependencyList"] = dependencyListElement.text();
            serviceMap["gameSize"] = gameSizeElement.text();
            serviceMap["downloadHooks"] = downloadHooksElement.text();
            serviceMap["executorHooks"] = executorHooksElement.text();
            serviceMap["isPublishedInApp"] = isPublishedInAppElement.text();
            serviceMap["iconInApp"] = iconInAppElement.text();

            this->_servicesData.push_back(serviceMap);
          }

          return false;
        }

        const QList<QMap<QString, QString>>& GetHosts::servicesData()
        {
          return this->_servicesData;
        }

      }
    }
  }
}