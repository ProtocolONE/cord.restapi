/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (�) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/Commands/User/GetUserMainInfo.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        GetUserMainInfo::GetUserMainInfo(QObject *parent) : CommandBase(parent)
        {
          this->appendParameter("method", "user.getMainInfo");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);

          this->_response = new Response::UserMainInfoResponse();
        }

        GetUserMainInfo::~GetUserMainInfo() 
        {
           delete this->_response;
        }
          
        bool GetUserMainInfo::callMethod( const QDomDocument& response )
        {
          QDomElement responseElement = response.documentElement();
          QDomElement mainInfoElement = responseElement.firstChildElement("mainInfo");

          if(mainInfoElement.isNull())
            return true;

          QDomElement el = mainInfoElement.firstChildElement("mmid");
          if(!el.isNull())
            this->_response->setMarketingId(el.text());

          el = mainInfoElement.firstChildElement("nickname");
          if(!el.isNull())
            this->_response->setNickname(el.text());

          el = mainInfoElement.firstChildElement("nametech");
          if(!el.isNull())
            this->_response->setNametech(el.text());

          el = mainInfoElement.firstChildElement("profile");
          if(!el.isNull())
            this->_response->setProfileUrl(el.text());
          
          el = mainInfoElement.firstChildElement("profile");
          if(!el.isNull())
            this->_response->setProfileUrl(el.text());

          el = mainInfoElement.firstChildElement("avatarSmall");
          if(!el.isNull())
            this->_response->setSmallAvatarUrl(el.text());

          el = mainInfoElement.firstChildElement("avatarMedium");
          if(!el.isNull())
            this->_response->setMediumAvatarUrl(el.text());

          el = mainInfoElement.firstChildElement("avatarLarge");
          if(!el.isNull())
            this->_response->setLargeAvatarUrl(el.text());

          el = mainInfoElement.firstChildElement("steamId");
          if(!el.isNull())
            this->_response->setSteamId(el.text());

          el = mainInfoElement.firstChildElement("sex");
          if(!el.isNull()) {
            bool res;
            int id = el.text().toInt(&res);
            if(res)
               this->_response->setSex(id);
          }

         return false;
        }
      }
    }
  }
}