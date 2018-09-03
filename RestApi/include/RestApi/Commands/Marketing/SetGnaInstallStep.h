#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>
#include <RestApi/ProtocolOneCredential.h>

#include <QtCore/QVariantMap>
#include <QtCore/QMetaType>

#include <QtXml/QDomDocument>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace Marketing {

		  // Метод сохраняет данные об инсталляции и запуске игр из ГНА
		  /*
		  Параметры
				string userId 				 Идентификатор пользователя в ProtocolOne
				string appKey 				 Персональный ключ пользователя для работы с внешними приложениями.
				string hwid 				 HWID
				string serviceId			 ID сервиса. Не нужен, если считаем первый запуск ГНА
				integer marketModuleTarget 	 ID выполняемой цели (см ниже)

				marketModuleTarget может принимать следующие значения

				36 - Первый запуск ГНА
				37 - Начало загрузки игры
				38 - Окончание загрузки игры
				39 - Инсталляция игры
				40 - Первый вход в игру
		*/

        class RESTAPI_EXPORT SetGnaInstallStep : public CommandBase
        {
          Q_OBJECT
        public:
          SetGnaInstallStep();
          ~SetGnaInstallStep();
          
          virtual bool callMethod(const QDomDocument& response);
          bool isSuccess();

          void setHwid(const QString& hwid);
          void setServiceId(const QString& serviceId);
          void setMarketingTarget(int marketingTarget);

          void setMarketingId(const QString& mid);
          void setParamsMap(const QVariantMap& params);

          void setUserId(const QString& userId);
          void setAppKey(const QString& appKey);
          
        private:
            bool _ok;

        };
      }
    }
  }
}

