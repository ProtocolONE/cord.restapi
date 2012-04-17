/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMANDS_USER_SETUSERACTIVITY_H_
#define _GGS_RESTAPI_COMMANDS_USER_SETUSERACTIVITY_H_

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtCore/QPointer>
#include <QtXml/QDomDocument>

namespace GGS {
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
#endif