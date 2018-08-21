#include <RestApi/Commands/User/Response/UserMainInfoResponse.h>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace User {
        namespace Response {

          UserMainInfoResponse::UserMainInfoResponse()
          {
          }

          UserMainInfoResponse::~UserMainInfoResponse()
          {
          }

          void UserMainInfoResponse::setMarketingId(QString val)
          {
            _marketingId = val;
          }

          QString UserMainInfoResponse::nickname() const
          {
            return _nickname;
          }

          QString UserMainInfoResponse::marketingId() const
          {
            return _marketingId;
          }

          void UserMainInfoResponse::setNickname(QString val)
          {
            _nickname = val;
          }

          QString UserMainInfoResponse::nametech() const
          {
            return _nametech;
          }

          void UserMainInfoResponse::setNametech(QString val)
          {
            _nametech = val;
          }

          int UserMainInfoResponse::sex() const
          {
            return _sex;
          }

          void UserMainInfoResponse::setSex(int val)
          {
            _sex = val;
          }

          QString UserMainInfoResponse::profileUrl() const
          {
            return _profileUrl;
          }

          void UserMainInfoResponse::setProfileUrl(QString val)
          {
            _profileUrl = val;
          }

          QString UserMainInfoResponse::smallAvatarUrl() const
          {
            return _smallAvatarUrl;
          }

          void UserMainInfoResponse::setSmallAvatarUrl(QString val)
          {
            _smallAvatarUrl = val;
          }

          QString UserMainInfoResponse::mediumAvatarUrl() const
          {
            return _mediumAvatarUrl;
          }

          void UserMainInfoResponse::setMediumAvatarUrl(QString val)
          {
            _mediumAvatarUrl = val;
          }

          QString UserMainInfoResponse::largeAvatarUrl() const
          {
            return _largeAvatarUrl;
          }

          void UserMainInfoResponse::setLargeAvatarUrl(QString val)
          {
            _largeAvatarUrl = val;
          }

          QString UserMainInfoResponse::steamId() const
          {
            return _steamId;
          }

          void UserMainInfoResponse::setSteamId(QString val)
          {
            _steamId = val;
          }

        }
      }
    }
  }
}
