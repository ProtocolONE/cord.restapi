#include <RestApi/Api/V1/GetHost.h>

#include <QtCore/QObject>
#include <QtCore/QJsonDocument>
#include <QtCore/QVariant>
#include <QtCore/QVariantList>

namespace P1 {
  namespace RestApi {
    namespace Api {
      namespace V1 {

        GetHost::GetHost(QObject *parent)
          : RestApiCommandBase(parent)
        {
          this->initDefaultParams();
        }

        GetHost::GetHost(const QString& gameId, QObject *parent /*= 0*/)
          : RestApiCommandBase(parent)
        {
          this->initDefaultParams();
          this->setGameId(gameId);
        }

        void GetHost::setGameId(const QString& value)
        {
          this->appendParameter("gameId", value);
        }

        void GetHost::setResponse(const QByteArray& data)
        {
          QJsonParseError err;
          QJsonDocument doc = QJsonDocument::fromJson(data, &err);
          if (doc.isNull()) {
            this->_errorCode = CommandBase::BadFormat;
            return;
          }

          QVariant result = doc.toVariant();
          if (!result.canConvert<QVariantList>()) {
            this->_errorCode = CommandBase::BadFormat;
            return;
          }

          QVariantList response = result.toList();

          Q_FOREACH(const QVariant& var, response) {
            if (!var.canConvert<QVariantMap>()) {
              continue;
            }

            QVariantMap item = var.toMap();

            QMap<QString, QString> serviceMap;
            QVariantMap game = item["game"].toMap();
            if (!game.contains("id"))
              continue;;

            serviceMap["serviceId"] = game["id"].toString();
            serviceMap["gameId"] = "1";// INFO removed
            serviceMap["folderName"] = item["folderName"].toString();

            serviceMap["name"] = game["name"].toString();
            serviceMap["torrentUrl"] = item["downloadTorrentDirectUrl"].toString();

            serviceMap["hasDownloadPath"] = item["hasDownloadPath"].toBool() ? "1" : "0";
            serviceMap["isBrowserGame"] = "0"; // INFO unsupported browser games
            
            serviceMap["extractorType"] = item["extractorType"].toString();
            serviceMap["executeUrl"] = item["executeUrl"].toString();
            serviceMap["dependencyList"] = item["dependencyList"].toString();
            serviceMap["gameSize"] = item["gameSize"].toString();

            serviceMap["downloadHooks"] = item["downloadHooks"].toString();
            serviceMap["executorHooks"] = item["executorHooks"].toString();

            serviceMap["isPublishedInApp"] = "1"; // UNDONE
            serviceMap["iconInApp"] = item["iconInApp"].toString();

            this->_servicesData.push_back(serviceMap);
          }
        }

        const QList<QMap<QString, QString>>& GetHost::servicesData()
        {
          return this->_servicesData;
        }

        void GetHost::initDefaultParams()
        {
          this->_getRequestMaxLength = -1; // Unsupported post request
          this->_isAuthRequire = false;
          this->_isCacheable = true;
          this->_version = "v1";
          this->_method = "app/hosts/";
        }

      }
    }
  }
}