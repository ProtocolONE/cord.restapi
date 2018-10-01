/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (�) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#ifndef _GGS_RESTAPI_REST_API_MANAGER_H_
#define _GGS_RESTAPI_REST_API_MANAGER_H_

#include <RestApi/restapi_global.h>
#include <RestApi/GameNetCredential.h>

#include <QtCore/QtConcurrentRun>

namespace GGS {
  namespace RestApi {
    class RequestInterface;
    class CommandBaseInterface;
    
    class RESTAPI_EXPORT RestApiManager
    {
    public:
      RestApiManager();
      ~RestApiManager();

      /// <summary>������ ����� ������� �������.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="uri">Url �� ������������ �������.</param>
      void setUri(const QString& uri);

      /// <summary>������������� �����, ����� ������� ����������� ����������� ��������.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="request">[in] If non-null, the request.</param>
      void setRequest(RequestInterface *request);

      /// <summary>��������� ��������.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="command">[in] If non-null, the command.</param>
      void execute(CommandBaseInterface *command);

      /// <summary>������ ����������� ��� ��� �������.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="credential">The credential.</param>
      void setCridential(const GameNetCredential &credential);

      /*!
        \fn credential
        \brief ���������� ������� ������ � ������� ������������.
      */
      const GameNetCredential &credential();
    private:
      RequestInterface *_request;
      QString _uri;

      GameNetCredential _credential;
    };
  }
}
#endif // _GGS_RESTAPI_REST_API_MANAGER_H_