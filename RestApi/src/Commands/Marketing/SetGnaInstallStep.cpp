/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/Commands/Marketing/SetGnaInstallStep.h"
#include <qdebug.h>

namespace GGS {
    namespace RestApi {
        namespace Commands {
            namespace Marketing {

                SetGnaInstallStep::SetGnaInstallStep(){
                    this->appendParameter("method", "user.setGnaInstallStep");
                    this->appendParameter("version", "1");
                    this->appendParameter("lang", "ru");
                    this->setAuthRequire(true);
                    this->_ok = false;
                }

                SetGnaInstallStep::~SetGnaInstallStep(){
                }

                void SetGnaInstallStep::setHwid( const QString& hwid )
                {
                    this->appendParameter("hwid", hwid);
                }
                void SetGnaInstallStep::setServiceId( int serviceId )
                {
                    this->appendParameter("serviceId", QString::number(serviceId));
                }
                void SetGnaInstallStep::setMarketModuleTarget( int marketModuleTarget )
                {
                    this->appendParameter("marketModuleTarget", QString::number(marketModuleTarget));
                }

                bool SetGnaInstallStep::callMethod( const QDomDocument& response ){
                    QDomElement el = response.documentElement().firstChildElement("status");

                    if(!el.isNull()) {
                        this->_ok = el.text() == "ok";
                        return false;
                    } 

                    return true;
                }
            }
        }
    }
}