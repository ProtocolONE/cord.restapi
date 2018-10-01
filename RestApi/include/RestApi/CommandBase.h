/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (�) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMAND_BASE_H_
#define _GGS_RESTAPI_COMMAND_BASE_H_

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBaseInterface.h>

#include <QMetaObject>

class QDomDocument;

namespace GGS {
    namespace RestApi {

        /* ������ ��� ����������� � ����� �������, � ���������� ����������
           ��������� ������ ����! ��������
            connect( abc, SIGNAL( result(GGS::RestApi::CommandBaseInterface::CommandResults ), ... ); // ���������

            connect( abc, SIGNAL( result(CommandResults ), ... ); // �����������, ���� ���� CommandResults ��������� � ������� ���������

          ������ ������������� ������:

            GameNetCredential auth;   // ����� ��� �������� �����������
            auth.setAppKey(QString("92da94c6a632951c8d588f596826bfd1470843f0"));
            auth.setUserId("400001000000172890");

            HttpCommandRequest request;
            FakeCache cache;
            request.setCache(&cache); // ���������� ���

            RestApiManager restapi;

            restapi.setUri(QString("http://api.gamenet.dev/restapi"));
            restapi.setCridential(auth);
            restapi.setRequest(&request);

            // ������������ � ������� ����������. ������ ������ ����� ������ � ����� ������, ���� ����
            // ��������� �����-���� ������. � ���������� ������� ���������� ��� ���������� �������.

            connect(&command, SIGNAL(result(GGS::RestApi::CommandBaseInterface::CommandResults)),
                    this,     SLOT(SetUserActivityResult(GGS::RestApi::CommandBaseInterface::CommandResults)));

                  
            // ������ ������ ��� ��������� � �������
            command.setGameId(71);

            // ��������� �������, ����� ���������� ����� ������ ������ result(GGS::RestApi::CommandBaseInterface::CommandResults)
            // � ��������������� �����.
            restapi.execute(&command);

            // ����� ����������, ��� ��������� ������ �� �������, ���������� ������������ ������, ��� ������ ������� ����.
            �������� ������� GetBalance, ����� ���� ������������ ������ getBalance(), ������� ����� ����� �������������� �����
            ���������� �������.

            ��������:

            restapi.execute(&command);

            ...

            void result(GGS::RestApi::CommandBaseInterface::CommandResults code)
            {
                if (code == GGS::RestApi::CommandBaseInterface::NoError)
                  command.getBlance(); // ��������� ������
            }

            ���� � ������� ������������ ���������� �����, �� ��� ����� ������ �� �� ����������� � �.� ����� Response
            ��� ��������� ��� ������. ��������:

              void GetUserServiceAccount::GetUserServiceAccountResult( GGS::RestApi::CommandBaseInterface::CommandResults code )
              {
	              if (code == GGS::RestApi::CommandBaseInterface::NoError){
		              command.response()->getLogin(); // �������� � �������
		              command.response()->getToken();
		              command.response()->getStatus();
		              command.response()->getPassword();
                  } else if (code == GGS::RestApi::CommandBaseInterface::GenericError)
		              // ������� �� ������
              }
        */
        class RESTAPI_EXPORT CommandBase : public QObject, public CommandBaseInterface
        {
            Q_OBJECT
        public:
            CommandBase();
            ~CommandBase();

            void setAuthRequire(bool isAuthRequire);
            void setCacheable(bool isCacheable);
            void setCacheTime(int cacheTime);
            void appendParameter(const QString& name, const QString& value);

            const QString& getGenericErrorMessage();
            const int getGenericErrorMessageCode();

            virtual const bool isRestapiOverrided() const;

            virtual const QString& restapiUrl() const;

            bool isAuthRequire();
            bool isCacheable();

            int cacheTime();

            const QMap<QString, QString>* commandParameters() const;

            bool resultCallback(CommandResults commandResultCode, QString response);
            bool errorResultParse(const QDomDocument& response);
            virtual bool callMethod(const QDomDocument& response);
            void setRestapiUrl(const QString& url);

        protected:
            QString genericErrorMessage;
            int genericErrorMessageCode;

        private:
            bool _isAuthRequire;
            bool _isCacheable;
            int _cacheTime;

            QString _restApiUrl;
            bool _isRestapiOverrided;

            QMap<QString, QString> _commandParameters;

        signals:
            void result(GGS::RestApi::CommandBaseInterface::CommandResults);
        };
    }
}
#endif // _GGS_RESTAPI_COMMAND_BASE_H_