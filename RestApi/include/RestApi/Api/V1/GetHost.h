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

        class RESTAPI_EXPORT GetHost : public P1::RestApi::Command::RestApiCommandBase
        {
          Q_OBJECT
        public:
          explicit GetHost(QObject *parent = 0);
          GetHost(const QString& gameId, QObject *parent = 0);

          virtual ~GetHost() = default;

          void setGameId(const QString& value);

          virtual void setResponse(const QByteArray& data) override;

          const QList<QMap<QString, QString>>& servicesData();

        private:
          void initDefaultParams();
          
          QList<QMap<QString, QString>> _servicesData;

        };


      }
    }
  }
}