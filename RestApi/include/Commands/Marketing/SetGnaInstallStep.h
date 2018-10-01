/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (�) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
 
#ifndef _GGS_RESTAPI_COMMANDS_MARKETING_SETGNAINSTALLSTEP_H_
#define _GGS_RESTAPI_COMMANDS_MARKETING_SETGNAINSTALLSTEP_H_

#include "restapi_global.h"
#include "CommandBase.h"

#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {
    namespace Commands {
      namespace Marketing {

		  // ����� ��������� ������ �� ����������� � ������� ��� �� ���
		  /*
		  ���������
				string userId 				 ������������� ������������ � GameNet
				string appKey 				 ������������ ���� ������������ ��� ������ � �������� ������������.
				string hwid 				 HWID
				string serviceId			 ID �������. �� �����, ���� ������� ������ ������ ���
				integer marketModuleTarget 	 ID ����������� ���� (�� ����)

				marketModuleTarget ����� ��������� ��������� ��������

				36 - ������ ������ ���
				37 - ������ �������� ����
				38 - ��������� �������� ����
				39 - ����������� ����
				40 - ������ ���� � ����
		*/

        class RESTAPI_EXPORT SetGnaInstallStep : public QObject,
          public CommandBase
        {
          Q_OBJECT
        public:
          SetGnaInstallStep();
          ~SetGnaInstallStep();
          
          virtual bool resultCallback( CommandResults commandResultCode, QString response );
        signals:
          void result(int resultCode);
		  // ���������� 0 ���� ������ �� ����������, 
		  // ���� ��������� �� 0, �� ������ ������� ���������.
        };
      }
    }
  }
}

#endif // _GGS_RESTAPI_COMMANDS_MARKETING_SETGNAINSTALLSTEP_H_