/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDS_GAMES_RESPONSE_MW2SERVERLISTRESPONSE_H
#define _GGS_RESTAPI_COMMANDS_GAMES_RESPONSE_MW2SERVERLISTRESPONSE_H

#include <RestApi/restapi_global.h>
#include <QtCore/QString>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Games {
        namespace Response {
          class RESTAPI_EXPORT Mw2ServerInfo
          {
          public:
            Mw2ServerInfo();
            virtual ~Mw2ServerInfo();

            quint32 id() const;
            void setId(quint32 val);

            quint32 position() const;
            void setPosition(quint32 val);

            const QString &name() const;
            void setName(QString val);

            const QString &address() const;
            void setAddress(QString val);

            quint32 status() const;
            void setStatus(quint32 val);

            bool isPinned() const;
            void setPinned(bool val);

            quint32 charCount() const;
            void setCharCount(quint32 val);
          private:
            quint32 _id;
            quint32 _position;
            QString _serverName;
            QString _address;
            quint32 _status;
            bool _pinned;
            quint32 _charCount;
          };
        }
      }
    }
  }
}

#endif // _GGS_RESTAPI_COMMANDS_GAMES_RESPONSE_MW2SERVERLISTRESPONSE_H
