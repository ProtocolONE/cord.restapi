/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (�) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_REQUESTINTERFACE_H_
#define _GGS_RESTAPI_REQUESTINTERFACE_H_

#include "CommandBaseArgumentWraper.h"
#include <QtCore/QString>
namespace GGS {
  namespace RestApi {

    /// <summary>Request interface. ���������� ������ ������� ���� ���������������.</summary>
    /// <remarks>Ilya.Tkachenko, 13.02.2012.</remarks>
    class RequestInterface{
    public:
      virtual ~RequestInterface() {};

       /// <summary>����������� ������ �� ������ ������ ��������. ��������� �������� � ������� ���������
       ///  ������, ��������� � �������.</summary>
       /// <remarks>Ilya.Tkachenko, 13.02.2012.</remarks>
       /// <param name="arguments">     [in] If non-null, the command.</param>
       virtual void execute(CommandBaseArgumentWraper &arguments) = 0;
    };

  }
}
#endif // _GGS_RESTAPI_REQUESTINTERFACE_H_