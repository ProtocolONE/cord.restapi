/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <RestApi/Commands/Games/Response/Mw2ServerListResponse.h>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Games {
        namespace Response {

          Mw2ServerInfo::Mw2ServerInfo()
            : _pinned(false),
              _status(0),
              _charCount(0)
          {
          }

          Mw2ServerInfo::~Mw2ServerInfo()
          {
          }

          quint32 Mw2ServerInfo::id() const
          {
            return this->_id;
          }

          void Mw2ServerInfo::setId(quint32 val)
          {
            this->_id = val;
          }

          quint32 Mw2ServerInfo::position() const
          {
            return this->_position;
          }

          void Mw2ServerInfo::setPosition(quint32 val)
          {
            this->_position = val;
          }

          const QString& Mw2ServerInfo::name() const
          {
            return this->_serverName;
          }

          void Mw2ServerInfo::setName(QString val)
          {
            this->_serverName = val;
          }

          const QString& Mw2ServerInfo::address() const
          {
            return this->_address;
          }

          void Mw2ServerInfo::setAddress(QString val)
          {
            this->_address = val;
          }

          quint32 Mw2ServerInfo::status() const
          {
            return this->_status;
          }

          void Mw2ServerInfo::setStatus(quint32 val)
          {
            this->_status = val;
          }

          bool Mw2ServerInfo::isPinned() const
          {
            return this->_pinned;
          }

          void Mw2ServerInfo::setPinned(bool val)
          {
            this->_pinned = val;
          }

          quint32 Mw2ServerInfo::charCount() const
          {
            return this->_charCount;
          }

          void Mw2ServerInfo::setCharCount(quint32 val)
          {
            this->_charCount = val;
          }
        }
      }
    }
  }
}