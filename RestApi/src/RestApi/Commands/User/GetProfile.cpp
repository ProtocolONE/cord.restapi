#include <RestApi/Commands/User/GetProfile.h>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace User {

        GetProfile::GetProfile(const QStringList& profileId, int shortInfo, QObject *parent)
          : _profileId(profileId), _shortInfo(shortInfo), CommandBase(parent)
        {
          this->_shortInfo = shortInfo;

          this->appendParameter("method", "user.getProfile");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "launcher_ru");
          this->appendParameter("shortInfo", QString::number(this->_shortInfo));
          if (!profileId.isEmpty())
            this->appendParameter("profileId", profileId.join(","));
          this->setAuthRequire(true);          
        }

        GetProfile::~GetProfile()
        {
        }

        bool GetProfile::callMethod(const QDomDocument& response)
        {
          QDomElement responseElement = response.documentElement();
          QDomElement userInfoElement = responseElement.firstChildElement("userInfo");

          if (userInfoElement.isNull())
            return true;

          for(QDomElement firstRow = userInfoElement.firstChildElement("row"); 
            !firstRow.isNull(); 
            firstRow = firstRow.nextSiblingElement("row")) 
          {
            QDomElement userIdElement = firstRow.firstChildElement("userId");

            if (userIdElement.isNull())
              return true;

            QDomElement shortInfoElement = firstRow.firstChildElement("shortInfo");

            if (shortInfoElement.isNull())
              continue;

            UserGetProfileResponse userProfile;
            userProfile.setUserid(userIdElement.text());
            userProfile.setNickname(shortInfoElement.firstChildElement("nickname").text());
            userProfile.setNametech(shortInfoElement.firstChildElement("nametech").text());
            userProfile.setProfileLink(shortInfoElement.firstChildElement("profile").text());
            userProfile.setRegisterDate(shortInfoElement.firstChildElement("registerDate").text());
            userProfile.setSex(shortInfoElement.firstChildElement("sex").text().toInt() );
            userProfile.setOnline(static_cast<bool>(shortInfoElement.firstChildElement("online").text().toInt()));
            userProfile.setHasAvatar(static_cast<bool>(shortInfoElement.firstChildElement("hasAvatar").text().toInt()));
            userProfile.setLastOnline(shortInfoElement.firstChildElement("lastOnline").text().toInt());
            userProfile.setAvatarSmall(shortInfoElement.firstChildElement("avatarSmall").text());
            userProfile.setAvatarMedium(shortInfoElement.firstChildElement("avatarMedium").text());
            userProfile.setAvatarLarge(shortInfoElement.firstChildElement("avatarLarge").text());
            userProfile.setIsFriend(static_cast<bool>(shortInfoElement.firstChildElement("isFriend").text().toInt()));
            userProfile.setHasInvite(static_cast<bool>(shortInfoElement.firstChildElement("hasInvite").text().toInt()));

            this->_userProfiles.insert(userProfile.userId(), userProfile);
          }
          
          return false;
        }

        void GetProfile::setProfileId(const QStringList& profileId)
        {
          if (profileId.isEmpty())
            return;

          this->_profileId = profileId;
          this->appendParameter("profileId", profileId.join(","));
        }

        const QStringList& GetProfile::profileId() const
        {
          return this->_profileId;
        }

        void GetProfile::setShortInfo(bool shortInfo)
        {
          this->_shortInfo = shortInfo;
          this->appendParameter("shortInfo", QString::number(this->_shortInfo));
        }

        bool GetProfile::hasShortInfo() const
        {
          return this->_shortInfo;
        }

        const GetProfileMap& GetProfile::response()
        {
          return this->_userProfiles;
        }
      }
    }
  }
}