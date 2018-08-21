#pragma once

#include <RestApi/restapi_global.h>

#include <QtCore/QObject>
#include <QtCore/QString>

namespace P1 {
  namespace RestApi {
    namespace Commands {
      namespace User {
        namespace Response {

          class RESTAPI_EXPORT UserGetProfileResponse : public QObject
          {
            Q_OBJECT

          public:
            UserGetProfileResponse();
            UserGetProfileResponse(const UserGetProfileResponse&);
            ~UserGetProfileResponse();

            /*
              27.06.2012 igor bugaaev
              Оператор присваивания нужен для возможности использования контейнеров типа QMap, QHash, ...
            */
            UserGetProfileResponse& operator=(const UserGetProfileResponse& userProfileResponse);

            void setNickname(const QString& nickname);
            void setNametech(const QString& nametech);
            void setProfileLink(const QString& profile);
            void setRegisterDate(const QString& registerDate);
            void setSex(int sex);
            void setOnline(bool online);
            void setUserid(const QString& userId);
            void setHasAvatar(bool hasAvatar);
            void setLastOnline(quint32 lastOnline);
            void setAvatarSmall(const QString avatarSmall);
            void setAvatarMedium(const QString avatarMedium);
            void setAvatarLarge(const QString avatarLarge);
            void setIsFriend(bool isFriend);
            void setHasInvite(bool hasInvite);

            const QString& nickname() const;
            const QString& nametech() const;
            const QString& profileLink() const;
            const QString& registerDate() const;
            const int sex() const;
            const bool online() const;
            const QString& userId() const;
            const bool& hasAvatar() const;
            const quint32 lastOnline() const;
            const QString& avatarSmall() const;
            const QString& avatarMedium() const;
            const QString& avatarLarge() const;
            const bool isFriend() const;
            const bool hasInvite() const;

          private:
            QString _nickname;
            QString _nametech;
            QString _profileLink;
            QString _registerDate;
            int _sex;
            int _online;
            QString _userId;
            bool _hasAvatar;
            quint32 _lastOnline;
            QString _avatarSmall;
            QString _avatarMedium;
            QString _avatarLarge;
            bool _isFriend;
            bool _hasInvite;
          };
        }
      }
    }
  }
}

