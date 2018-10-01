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

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>

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

        class RESTAPI_EXPORT SetGnaInstallStep :
          public CommandBase
        {
          Q_OBJECT
        public:
          SetGnaInstallStep();
          ~SetGnaInstallStep();
          
          virtual bool SetGnaInstallStep::callMethod( const QDomDocument& response );
          bool getIsOk() { return _ok; }

          void setHwid( const QString& hwid );
          void setServiceId( int serviceId );
          void setMarketModuleTarget( int marketModuleTarget );

        private:
            bool _ok;
        };
      }
    }
  }
}

#endif // _GGS_RESTAPI_COMMANDS_MARKETING_SETGNAINSTALLSTEP_H_