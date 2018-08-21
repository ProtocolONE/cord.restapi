#include <RestApi/Commands/User/SetUserActivity.h>

#include <qdebug.h>
#include <qdatetime>

namespace P1 {
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