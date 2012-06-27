/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDS_USER_GETPROFILE_H_
#define _GGS_RESTAPI_COMMANDS_USER_GETPROFILE_H_

#include <RestApi/Commands/User/Response/UserGetProfileResponse.h>

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtXml/QDomDocument>
#include <QtCore/QStringList>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        using namespace GGS::RestApi::Commands::User::Response;

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

          const QMap<QString, UserGetProfileResponse>& response();

        private:
          QStringList _profileId;
          bool _shortInfo;
          QMap<QString, UserGetProfileResponse> _userProfiles;
        };
      }
    }
  }
}

#endif // GETPROFILE_H
