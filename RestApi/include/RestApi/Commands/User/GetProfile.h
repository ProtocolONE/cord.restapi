#pragma once
#include <RestApi/Commands/User/Response/UserGetProfileResponse.h>

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>
#include <QtCore/QStringList>
#include <QtCore/QMap>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace User {

        using namespace P1::RestApi::Commands::User::Response;

        typedef QMap<QString, P1::RestApi::Commands::User::UserGetProfileResponse> GetProfileMap;

        class RESTAPI_EXPORT GetProfile : public CommandBase
        {
          Q_OBJECT

        public:
          GetProfile(const QStringList& profileId = QStringList(), int shortInfo = 1, QObject *parent = 0);
          ~GetProfile();

          virtual bool callMethod(const QDomDocument& response);

          void setProfileId(const QStringList& profileId);
          void setShortInfo(bool shortInfo);

          const QStringList& profileId() const;       
          bool hasShortInfo() const;

          const GetProfileMap& response();

        private:
          QStringList _profileId;
          bool _shortInfo;
          GetProfileMap _userProfiles;
        };
      }
    }
  }
}

