#ifndef _GGS_RESTAPI_COMMANDS_USER_RESPONSE_USERMAININFORESPONSE_H_
#define _GGS_RESTAPI_COMMANDS_USER_RESPONSE_USERMAININFORESPONSE_H_

#include "restapi_global.h"
#include <QtCore/QObject>
#include <QtCore/QString>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {
        namespace Response {

          class RESTAPI_EXPORT UserMainInfoResponse : public QObject
          {
            Q_OBJECT
          public:
            UserMainInfoResponse();
            ~UserMainInfoResponse();

            QString marketingId() const { return _marketingId; }
            void setMarketingId(QString val) { _marketingId = val; }
            
            QString nickname() const { return _nickname; }
            void setNickname(QString val) { _nickname = val; }

            QString nametech() const { return _nametech; }
            void setNametech(QString val) { _nametech = val; }

            int sex() const { return _sex; }
            void setSex(int val) { _sex = val; }

            QString profileUrl() const { return _profileUrl; }
            void setProfileUrl(QString val) { _profileUrl = val; }

            QString smallAvatarUrl() const { return _smallAvatarUrl; }
            void setSmallAvatarUrl(QString val) { _smallAvatarUrl = val; }

            QString mediumAvatarUrl() const { return _mediumAvatarUrl; }
            void setMediumAvatarUrl(QString val) { _mediumAvatarUrl = val; }

            QString largeAvatarUrl() const { return _largeAvatarUrl; }
            void setLargeAvatarUrl(QString val) { _largeAvatarUrl = val; }

            QString steamId() const { return _steamId; }
            void setSteamId(QString val) { _steamId = val; }

          private:
            QString _marketingId;
            QString _nickname;
            QString _nametech;
            // UNDONE: may be enum?
            int _sex;
            QString _profileUrl;
            QString _smallAvatarUrl;
            QString _mediumAvatarUrl;
            QString _largeAvatarUrl;
            QString _steamId;
          };

        }
      }
    }
  }
}
#endif // _GGS_RESTAPI_COMMANDS_USER_RESPONSE_USERMAININFORESPONSE_H_