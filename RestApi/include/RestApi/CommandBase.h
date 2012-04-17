/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
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
#include <qdom.h>

namespace GGS {
    namespace RestApi {

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

            const QString& getGenericErrorMessage() { return this->genericErrorMessage; }
            const int getGenericErrorMessageCode() { return this->genericErrorMessageCode; }

            virtual const bool isRestapiOverrided() const { return this->_isRestapiOverrided; }

            virtual const QString& restapiUrl() const { return this->_restApiUrl; }

            bool isAuthRequire();
            bool isCacheable();

            int cacheTime();

            const QMap<QString, QString>* commandParameters() const;

            bool resultCallback( CommandResults commandResultCode, QString response );
            bool errorResultParse( const QDomDocument& response );
            virtual bool callMethod( const QDomDocument& response );
            void setRestapiUrl( const QString& url );

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

            /* Всегда пля подключения к этому сигналу, в параметрах необходимо
               указывать полный путь! Например
                 connect( abc, SIGNAL( result(GGS::RestApi::CommandBaseInterface::CommandResults ), ... ); // ПРАВИЛЬНО

                 connect( abc, SIGNAL( result(CommandResults ), ... ); // НЕПРАВИЛЬНО, даже если CommandResults находится в области видимости

                Пример использования команд:

                  GameNetCredential auth;   // Класс для хранения авторизации
                  auth.setAppKey(QString("92da94c6a632951c8d588f596826bfd1470843f0"));
                  auth.setUserId("400001000000172890");

                  HttpCommandRequest request;
                  FakeCache cache;
                  request.setCache(&cache); // Подключаем кэш

                  RestApiManager restapi;

                  restapi.setUri(QString("http://api.gamenet.dev/restapi"));
                  restapi.setCridential(auth);
                  restapi.setRequest(&request);

                  // Подключаемся к сигналу результата. Данный сигнал будет вызван в любом случае, даже если
                  // произошла какая-либо ошибка. В параметрах сигнала передается код выполнения команды.

                  connect(&command, SIGNAL(result(GGS::RestApi::CommandBaseInterface::CommandResults)),
                          this,     SLOT(SetUserActivityResult(GGS::RestApi::CommandBaseInterface::CommandResults)));

                  
                  // Задаем нужные нам параметры к команде
                  command.setGameId(71);

                  // Выполняем команду, после выполнения будет вызван сигнал result(GGS::RestApi::CommandBaseInterface::CommandResults)
                  // с соответствующим кодом.
                  restapi.execute(&command);

                  // После выполнения, для получения ответа от сервера, необходимо использовать геттер, для каждой команды свой.
                  Например команда GetBalance, имеет один единственный геттер getBalance(), которым можно будет воспользоватся после
                  выполнения команды.

                  Например:

                  restapi.execute(&command);

                  ...

                  void result(GGS::RestApi::CommandBaseInterface::CommandResults code)
                  {
                     if (code == GGS::RestApi::CommandBaseInterface::NoError)
                        command.getBlance(); // возвратит баланс
                  }

                  Если у команды возвращаемых параметров много, то для этого случая мы их оборачиваем в т.н класс Response
                  где групируем все данные. Например:

                    void GetUserServiceAccount::GetUserServiceAccountResult( GGS::RestApi::CommandBaseInterface::CommandResults code )
                    {
	                    if (code == GGS::RestApi::CommandBaseInterface::NoError){
		                    command.response()->getLogin(); // работаем с данными
		                    command.response()->getToken();
		                    command.response()->getStatus();
		                    command.response()->getPassword();
                        } else if (code == GGS::RestApi::CommandBaseInterface::GenericError)
		                    // реакция на ошибку
                    }



              */

        };
    }
}
#endif // _GGS_RESTAPI_COMMAND_BASE_H_