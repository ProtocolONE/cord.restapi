/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2017, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/RequestBase.h>

#include <QtCore/QList>
#include <QtCore/QPointer>
#include <QtNetwork/QSslError>

class QNetworkAccessManager;
class QNetworkReply;

namespace GGS {
  namespace RestApi {
    class RESTAPI_EXPORT HttpCommandRequest : public RequestBase
    {
      Q_OBJECT
    public:
      explicit HttpCommandRequest(QObject *parent = 0);
      virtual ~HttpCommandRequest(void);

      /*!
        \fn void HttpCommandRequest::execute(const QUrl &request);
      
        \brief Executes.
      
        \param request The request.
      */
      void execute(const QUrl &request);

    private slots:
      void requestFinish();
      void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

    private:
      QPointer<QNetworkAccessManager> _networkManager;

      /*!< Используется для удобства отладки, чтобы было легко понять какая комманда упала. */
      QString _requestString;
    };
  }
}
