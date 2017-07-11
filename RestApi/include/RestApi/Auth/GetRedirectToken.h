/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates.
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

#include <QtCore/QPointer>
#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Auth {

      class RESTAPI_EXPORT GetRedirectToken :
        public CommandBase
      {
        Q_OBJECT
      public:
        GetRedirectToken(QObject *parent = 0);
        ~GetRedirectToken();

        virtual bool callMethod(const QDomDocument& response);

        const QString& token() const;

      private:
        QString _token;
      };

    }
  }
}
