#pragma once

#include <RestApi/restapi_global.h>

#include <RestApi/Command/RestApiCommandBase.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDateTime>

namespace P1 {
  namespace RestApi {
    namespace Api {
      namespace V1 {
        namespace Auth {

          class RESTAPI_EXPORT Refresh : public P1::RestApi::Command::RestApiCommandBase
          {
            Q_OBJECT
          public:
            explicit Refresh(QObject *parent = 0);
            Refresh(const QString& refreshToken, QObject *parent = 0);

            virtual ~Refresh() = default;

            void setRefreshToken(const QString& value);

            virtual void setResponse(const QByteArray& data) override;

            const QString& accessToken() const;
            const QDateTime& acccessTokenExpiredTime() const;

            const QString& refreshToken() const;
            const QDateTime& refreshTokenExpiredTime() const;

          private:
            void initDefaultParams();

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
