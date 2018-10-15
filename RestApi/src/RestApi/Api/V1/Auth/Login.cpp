#include <RestApi/Api/V1/Auth/Login.h>

#include <QtCore/QJsonDocument>

namespace P1 {
  namespace RestApi {
    namespace Api {
      namespace V1 {
        namespace Auth {

          Login::Login(QObject *parent)
            : JsonCommand(parent)
          {
            this->initDefaultParams();
          }

          Login::Login(const QString& login, const QString& password, const QString& captcha, QObject *parent /*= 0*/)
            : JsonCommand(parent)
          {
            this->initDefaultParams();
            this->setLogin(login);
            this->setPassword(password);
            this->setCaptcha(captcha);
          }

          void Login::initDefaultParams()
          {
            this->_isAuthRequire = false;
            this->_isCacheable = false;
            this->_version = "v1";
            this->_method = "user/login";
          }

          void Login::initErrors()
          {
            this->setError(400, Login::InvalidUserNameOrPassword);
            this->setError(429, Login::CaptchaRequired);
            this->setError(426, Login::TemporaryLock);
          }

          void Login::setLogin(const QString& value)
          {
            this->_params["email"] = value;
          }

          void Login::setPassword(const QString& value)
          {
            this->_params["password"] = value;
          }

          void Login::setCaptcha(const QString& value)
          {
            this->_params["captcha"] = value;
          }

          void Login::setResponse(const QByteArray& data)
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

          const QString& Login::accessToken() const
          {
            return this->_accessToken;
          }

          const QDateTime& Login::acccessTokenExpiredTime() const
          {
            return this->_acccessTokenExpiredTime;
          }

          const QString& Login::refreshToken() const
          {
            return this->_refreshToken;
          }

          const QDateTime& Login::refreshTokenExpiredTime() const
          {
            return this->_refreshTokenExpiredTime;
          }
        }
      }
    }
  }
}
