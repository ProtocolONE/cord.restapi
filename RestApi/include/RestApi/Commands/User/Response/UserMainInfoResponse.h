#pragma once

#include <RestApi/restapi_global.h>

#include <QtCore/QObject>
#include <QtCore/QString>

namespace P1 {
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

            QString marketingId() const;
            void setMarketingId(QString val);
            
            QString nickname() const;
            void setNickname(QString val);

            QString nametech() const;
            void setNametech(QString val);

            int sex() const;
            void setSex(int val);

            QString profileUrl() const;
            void setProfileUrl(QString val);

            QString smallAvatarUrl() const;
            void setSmallAvatarUrl(QString val);

            QString mediumAvatarUrl() const;
            void setMediumAvatarUrl(QString val);

            QString largeAvatarUrl() const;
            void setLargeAvatarUrl(QString val);

            QString steamId() const;
            void setSteamId(QString val);

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
