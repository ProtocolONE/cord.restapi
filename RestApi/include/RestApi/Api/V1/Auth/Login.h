#pragma once

#include <RestApi/restapi_global.h>

#include <RestApi/Command/JsonCommand.h>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDateTime>

namespace P1 {
  namespace RestApi {
    namespace Api {
      namespace V1 {
        namespace Auth {

          class RESTAPI_EXPORT Login : public P1::RestApi::Command::JsonCommand
          {
            Q_OBJECT
          public:
            enum Result : uint32_t {
              InvalidUserNameOrPassword = CommandBase::CommandCustom + 1,
              CaptchaRequired,
              TemporaryLock
            };

            explicit Login(QObject *parent = 0);
            Login(const QString& login, const QString& password, const QString& captcha, QObject *parent = 0);

            virtual ~Login() = default;

            void setLogin(const QString& value);
            void setPassword(const QString& value);
            void setCaptcha(const QString& value);

            virtual void setResponse(const QByteArray& data) override;

            const QString& accessToken() const;
            const QDateTime& acccessTokenExpiredTime() const;

            const QString& refreshToken() const;
            const QDateTime& refreshTokenExpiredTime() const;

          private:
            void initDefaultParams();
            void initErrors();

            QString _accessToken;
            QDateTime _acccessTokenExpiredTime;

            QString _refreshToken;
            QDateTime _refreshTokenExpiredTime;
          };

        }
      }
    }
  }
}
