/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/Commands/User/Response/UserGetProfileResponse.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {
        namespace Response {

          UserGetProfileResponse::UserGetProfileResponse()
          {
          }

          UserGetProfileResponse::UserGetProfileResponse(const UserGetProfileResponse& userProfileResponse)
          {
            this->operator=(userProfileResponse);
          }

          UserGetProfileResponse& UserGetProfileResponse::operator= (const UserGetProfileResponse& userProfileResponse)
          {
            if (this != &userProfileResponse) 
            {
              this->_nickname = userProfileResponse.nickname();
              this->_nametech = userProfileResponse.nametech();
              this->_profileLink = userProfileResponse.profileLink();
              this->_registerDate = userProfileResponse.registerDate();
              this->_sex = userProfileResponse.sex();
              this->_online = userProfileResponse.online();
              this->_userId = userProfileResponse.userId();
              this->_hasAvatar = userProfileResponse.hasAvatar();
              this->_lastOnline = userProfileResponse.lastOnline();
              this->_avatarSmall = userProfileResponse.avatarSmall();
              this->_avatarMedium = userProfileResponse.avatarMedium();
              this->_avatarLarge = userProfileResponse.avatarLarge();
              this->_isFriend = userProfileResponse.isFriend();
              this->_hasInvite = userProfileResponse.hasInvite();
            }

            return *this;
          }

          UserGetProfileResponse::~UserGetProfileResponse()
          {
          }

          void UserGetProfileResponse::setNickname( const QString& nickname )
          {
            this->_nickname = nickname;
          }

          void UserGetProfileResponse::setNametech( const QString& nametech )
          {
            this->_nametech = nametech;
          }

          void UserGetProfileResponse::setProfileLink( const QString& profile )
          {
            this->_profileLink = profile;
          }

          void UserGetProfileResponse::setRegisterDate(const QString& registerDate)
          {
            this->_registerDate = registerDate;
          }

          void UserGetProfileResponse::setSex( int sex )
          {
            this->_sex = sex;
          }

          void UserGetProfileResponse::setOnline( bool online )
          {
            this->_online = online;
          }

          void UserGetProfileResponse::setUserid( const QString& userId )
          {
            this->_userId = userId;
          }

          void UserGetProfileResponse::setHasAvatar( bool hasAvatar )
          {
            this->_hasAvatar = hasAvatar;
          }

          void UserGetProfileResponse::setLastOnline( quint32 lastOnline )
          {
            this->_lastOnline = lastOnline;
          }

          void UserGetProfileResponse::setAvatarSmall( const QString avatarSmall )
          {
            this->_avatarSmall = avatarSmall;
          }

          void UserGetProfileResponse::setAvatarMedium( const QString avatarMedium )
          {
            this->_avatarMedium = avatarMedium;
          }

          void UserGetProfileResponse::setAvatarLarge( const QString avatarLarge )
          {
            this->_avatarLarge = avatarLarge;
          }

          void UserGetProfileResponse::setIsFriend( bool isFriend )
          {
            this->_isFriend = isFriend;
          }

          void UserGetProfileResponse::setHasInvite( bool hasInvite )
          {
            this->_hasInvite = hasInvite;
          }

          const QString& UserGetProfileResponse::nickname() const
          {
            return this->_nickname;
          }

          const QString& UserGetProfileResponse::nametech() const
          {
            return this->_nametech;
          }

          const QString& UserGetProfileResponse::profileLink() const
          {
            return this->_profileLink;
          }

          const QString& UserGetProfileResponse::registerDate() const
          {
            return this->_registerDate;
          }

          const int UserGetProfileResponse::sex() const
          {
            return this->_sex;
          }

          const bool UserGetProfileResponse::online() const
          {
            return this->_online;
          }

          const QString& UserGetProfileResponse::userId() const
          {
            return this->_userId;
          }

          const bool& UserGetProfileResponse::hasAvatar() const
          {
            return this->_hasAvatar;
          }

          const quint32 UserGetProfileResponse::lastOnline() const
          {
            return this->_lastOnline;
          }

          const QString& UserGetProfileResponse::avatarSmall() const
          {
            return this->_avatarSmall;
          }

          const QString& UserGetProfileResponse::avatarMedium() const
          {
            return this->_avatarMedium;
          }

          const QString& UserGetProfileResponse::avatarLarge() const
          {
            return this->_avatarLarge;
          }

          const bool UserGetProfileResponse::isFriend() const
          {
            return this->_isFriend;
          }

          const bool UserGetProfileResponse::hasInvite() const
          {
            return this->_hasInvite;
          }
        }
      }
    }
  }
}