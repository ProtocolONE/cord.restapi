/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/Commands/User/SetUserActivity.h"

#include <qdebug.h>
#include <qdatetime>

namespace GGS {
    namespace RestApi {
        namespace Commands {
            namespace User {

                SetUserActivity::SetUserActivity(){
                    this->appendParameter("method", "user.setActivityUser");
                    this->appendParameter("version", "1");
                    this->appendParameter("lang", "ru");
                    this->setAuthRequire(true);
                    this->_timeout = 0;
                }

                SetUserActivity::~SetUserActivity(){
                }

                int SetUserActivity::getTimeout() { return _timeout; }

                void SetUserActivity::setGameId( int gameId )
                {
                    this->appendParameter("gameId", QString::number(gameId));
                }
                void SetUserActivity::setLogout( int logout )
                {
                    this->appendParameter("logout", QString::number(logout));
                }

                bool SetUserActivity::callMethod( const QDomDocument& response )
                {
                    QDomElement responseElement = response.documentElement();

                    if(responseElement.isNull())
                        return true;

                    QDomElement el = responseElement.firstChildElement("timeout");
                    if(!el.isNull()) {
                        _timeout = el.text().toInt();
                        return false;
                    }

                    return true;
                }
            }
        }
    }
}