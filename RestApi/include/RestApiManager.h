/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_REST_API_MANAGER_H_
#define _GGS_RESTAPI_REST_API_MANAGER_H_

#include "restapi_global.h"
#include "CommandBaseInterface.h"
#include "HttpCommandRequest.h"
#include "CommandBaseArgumentWraper.h"
#include "GameNetCredential.h"

#include <QtCore/QtConcurrentRun>

namespace GGS {
  namespace RestApi {
    class RESTAPI_EXPORT RestApiManager
    {
    public:
      RestApiManager(void);
      ~RestApiManager(void);

      /// <summary>Задает адрес рестапи сервера.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="uri">Url до рестапишного сервера.</param>
      void setUri(const QString& uri) { this->_uri = uri; }

      /// <summary>Устанавливает класс, через который выполняются рестапишные комманды.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="request">[in] If non-null, the request.</param>
      void setRequest(RequestInterface *request) { this->_request = request; }

      /// <summary>Выполняет комманду.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="command">[in] If non-null, the command.</param>
      void execute(CommandBaseInterface *command);

      /// <summary>Задает авторизацию для все комманд.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="credential">The credential.</param>
      void setCridential(const GameNetCredential &credential) { this->_credential = credential; }
    private:
      RequestInterface *_request;
      QString _uri;

      GameNetCredential _credential;
    };
  }
}
#endif // _GGS_RESTAPI_REST_API_MANAGER_H_