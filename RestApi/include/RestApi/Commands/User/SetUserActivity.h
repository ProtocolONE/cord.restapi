#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtCore/QPointer>
#include <QtXml/QDomDocument>

namespace P1 {
    namespace RestApi {
        namespace Commands {
            namespace User {

                class RESTAPI_EXPORT SetUserActivity : 
                    public CommandBase
                {
                    Q_OBJECT
                public:
                    SetUserActivity();
                    ~SetUserActivity();

                    virtual bool callMethod( const QDomDocument& response );

                    int getTimeout();

                    void setGameId( int gameId );
                    void setLogout( int logout );

                private:
                    int _timeout;
                };

            }
        }
    }
}
