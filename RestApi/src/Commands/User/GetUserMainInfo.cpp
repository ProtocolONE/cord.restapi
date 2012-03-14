#include "Commands/User/GetUserMainInfo.h"

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace User {

        GetUserMainInfo::GetUserMainInfo(void)
        {
          this->appendParameter("method", "user.getMainInfo");
          this->appendParameter("version", "1");
          this->appendParameter("lang", "ru");
          this->setAuthRequire(true);

          _response = NULL;
        }


        GetUserMainInfo::~GetUserMainInfo(void)
        {
           delete this->_response;
        }

        void GetUserMainInfo::resultCallback( CommandResults commandResultCode, QString response )
        {
          if(commandResultCode != CommandResults::NoError) {
            this->_resultCode = commandResultCode;
            emit this->result();
            return;
          }

          this->_response = new Response::UserMainInfoResponse();

          QDomDocument doc;
          if (!doc.setContent(response)) {
            this->_resultCode = CommandResults::XmlError;
            emit this->result();
            return;
          }

          QDomElement responseElement = doc.documentElement();
          QDomElement mainInfoElement = responseElement.firstChildElement("mainInfo");

          if(mainInfoElement.isNull()) {
            this->_resultCode = CommandResults::XmlError;
            emit this->result();
            return;
          }

          QDomElement el = mainInfoElement.firstChildElement("mmid");
          if(!el.isNull()) {
            this->_response->setMarketingId(el.text());
          }

          el = mainInfoElement.firstChildElement("nickname");
          if(!el.isNull()) {
            this->_response->setNickname(el.text());
          }

          el = mainInfoElement.firstChildElement("nametech");
          if(!el.isNull()) {
            this->_response->setNametech(el.text());
          }

          el = mainInfoElement.firstChildElement("profile");
          if(!el.isNull()) {
            this->_response->setProfileUrl(el.text());
          }
          
          el = mainInfoElement.firstChildElement("profile");
          if(!el.isNull()) {
            this->_response->setProfileUrl(el.text());
          }

          el = mainInfoElement.firstChildElement("avatarSmall");
          if(!el.isNull()) {
            this->_response->setSmallAvatarUrl(el.text());
          }

          el = mainInfoElement.firstChildElement("avatarMedium");
          if(!el.isNull()) {
            this->_response->setMediumAvatarUrl(el.text());
          }

          el = mainInfoElement.firstChildElement("avatarLarge");
          if(!el.isNull()) {
            this->_response->setLargeAvatarUrl(el.text());
          }

          el = mainInfoElement.firstChildElement("steamId");
          if(!el.isNull()) {
            this->_response->setSteamId(el.text());
          }

          el = mainInfoElement.firstChildElement("sex");
          if(!el.isNull()) {
            bool res;
            int id = el.text().toInt(&res);
            if(res){
               this->_response->setSex(id);
            }
          }

          this->_resultCode = CommandResults::NoError;
          emit this->result();
        }

      }
    }
  }
}