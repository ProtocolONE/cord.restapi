#include <RestApi/Api/V1/Auth/Refresh.h>

#include <QtCore/QJsonDocument>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>

namespace P1 {
  namespace RestApi {
    namespace Api {
      namespace V1 {
        namespace Auth {

          Refresh::Refresh(QObject *parent)
            : RestApiCommandBase(parent)
          {
            this->initDefaultParams();
          }

          Refresh::Refresh(const QString& refreshToken, QObject *parent /*= 0*/)
            : RestApiCommandBase(parent)
          {
            this->initDefaultParams();
            this->setRefreshToken(refreshToken);
          }

          void Refresh::initDefaultParams()
          {
            this->_getRequestMaxLength = -1; // Unsupported post request
            this->_isAuthRequire = false;
            this->_isCacheable = false;
            this->_version = "v1";
            this->_method = "token/refresh/";
          }

          void Refresh::setRefreshToken(const QString& value)
          {
            this->_method = QString("token/refresh/%1").arg(value);
          }

          void Refresh::setResponse(const QByteArray& data)
          {
            QJsonParseError err;
            QJsonDocument doc = QJsonDocument::fromJson(data, &err);
            if (doc.isNull()) {
              this->_errorCode = CommandBase::BadFormat;
              return;
            }

            QVariant result = doc.toVariant();
            if (!result.canConvert<QVariantMap>()) {
              this->_errorCode = CommandBase::BadFormat;
              return;
            }

            QVariantMap response = result.toMap();
            if (!response.contains("accessToken") ||
              !response.contains("refreshToken")) {
              this->_errorCode = CommandBase::BadFormat;
              return;
            }

            QVariant accessTokenVariant = response["accessToken"];
            QVariant refreshTokenVariant = response["refreshToken"];
            if (!accessTokenVariant.canConvert<QVariantMap>() ||
              !refreshTokenVariant.canConvert<QVariantMap>()) {
              this->_errorCode = CommandBase::BadFormat;
              return;
            }

            QVariantMap accessToken = accessTokenVariant.toMap();
            QVariantMap refreshToken = refreshTokenVariant.toMap();
            if (!accessToken.contains("value") || !accessToken.contains("exp")
              || !refreshToken.contains("value") || !refreshToken.contains("exp")) {
              this->_errorCode = CommandBase::BadFormat;
              return;
            }

            QString accessTokenValue = accessToken["value"].toString();
            QString refreshTokenValue = refreshToken["value"].toString();
            if (accessTokenValue.isEmpty() || refreshTokenValue.isEmpty()) {
              this->_errorCode = CommandBase::BadFormat;
              return;
            }

            QString accessTokenExpTimeValue = accessToken["exp"].toString();
            QString refreshTokenExpTimeValue = refreshToken["exp"].toString();
            bool ok, ok2;
            qint64 at, rt;
            at = accessTokenExpTimeValue.toLongLong(&ok);
            rt = refreshTokenExpTimeValue.toLongLong(&ok2);
            if (!ok || !ok2) {
              this->_errorCode = CommandBase::BadFormat;
              return;
            }

            this->_accessToken = accessTokenValue;
            this->_refreshToken = refreshTokenValue;
            this->_acccessTokenExpiredTime = QDateTime::fromMSecsSinceEpoch(at * 1000);
            this->_refreshTokenExpiredTime = QDateTime::fromMSecsSinceEpoch(rt * 1000);
          }

          const QString& Refresh::accessToken() const
          {
            return this->_accessToken;
          }

          const QDateTime& Refresh::acccessTokenExpiredTime() const
          {
            return this->_acccessTokenExpiredTime;
          }

          const QString& Refresh::refreshToken() const
          {
            return this->_refreshToken;
          }

          const QDateTime& Refresh::refreshTokenExpiredTime() const
          {
            return this->_refreshTokenExpiredTime;
          }
        }
      }
    }
  }
}

