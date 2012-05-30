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

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QUrl>

class QDomDocument;

namespace GGS {
  namespace RestApi {

    /* Всегда пля подключения к этому сигналу, в параметрах необходимо
    указывать полный путь! Например
    connect( abc, SIGNAL( result(GGS::RestApi::CommandBase::CommandResults ), ... ); // ПРАВИЛЬНО

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

    connect(&command, SIGNAL(result(GGS::RestApi::CommandBase::CommandResults)),
    this,     SLOT(SetUserActivityResult(GGS::RestApi::CommandBase::CommandResults)));


    // Задаем нужные нам параметры к команде
    command.setGameId(71);

    // Выполняем команду, после выполнения будет вызван сигнал result(GGS::RestApi::CommandBase::CommandResults)
    // с соответствующим кодом.
    restapi.execute(&command);

    // После выполнения, для получения ответа от сервера, необходимо использовать геттер, для каждой команды свой.
    Например команда GetBalance, имеет один единственный геттер getBalance(), которым можно будет воспользоватся после
    выполнения команды.

    Например:

    restapi.execute(&command);

    ...

    void result(GGS::RestApi::CommandBase::CommandResults code)
    {
    if (code == GGS::RestApi::CommandBase::NoError)
    command.getBlance(); // возвратит баланс
    }

    Если у команды возвращаемых параметров много, то для этого случая мы их оборачиваем в т.н класс Response
    где групируем все данные. Например:

    void GetUserServiceAccount::GetUserServiceAccountResult( GGS::RestApi::CommandBase::CommandResults code )
    {
    if (code == GGS::RestApi::CommandBase::NoError){
    command.response()->getLogin(); // работаем с данными
    command.response()->getToken();
    command.response()->getStatus();
    command.response()->getPassword();
    } else if (code == GGS::RestApi::CommandBase::GenericError)
    // реакция на ошибку
    }
    */
    class RESTAPI_EXPORT CommandBase : public QObject
    {
      Q_OBJECT
      Q_ENUMS(GGS::RestApi::CommandBase::CommandResults);
    public:
      enum CommandResults{
        NoError = 0,
        NetworkError = 1,
        GenericError = 2,
        XmlError = 3
      };

      explicit CommandBase(QObject *parent = 0);
      virtual ~CommandBase();

      void setAuthRequire(bool isAuthRequire);
      virtual bool isAuthRequire();

      void setCacheable(bool isCacheable);
      virtual bool isCacheable();

      void setCacheTime(int cacheTime);
      virtual int cacheTime();

      virtual void setRestapiUrl(const QString& url);
      virtual const QString& restapiUrl() const;
      virtual const bool isRestapiOverrided() const;

      virtual void appendParameter(const QString& name, const QString& value);
      virtual const QMap<QString, QString>* commandParameters() const;

      /*!
        \fn const QString& CommandBase::getGenericErrorMessage();
      
        \brief Gets the generic error message.
      
        \return The generic error message.

        \deprecated Use errorMessage
      */
      const QString& getGenericErrorMessage();

      /*!
        \fn const int CommandBase::getGenericErrorMessageCode();
      
        \brief Gets the generic error message code.
      
        \return The generic error message code.

        \deprecated use errorCode
      */

      const int getGenericErrorMessageCode();

      const QString& errorMessage();
      const int errorCode();
      
      virtual bool errorResultParse(const QDomDocument& response);
      virtual bool callMethod(const QDomDocument& response);
      
      const QUrl url();
    public slots:
      void resultCallback(GGS::RestApi::CommandBase::CommandResults commandResultCode, QString response);

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
      void result(GGS::RestApi::CommandBase::CommandResults);
    };
  }
}

Q_DECLARE_METATYPE(GGS::RestApi::CommandBase::CommandResults);

#endif // _GGS_RESTAPI_COMMAND_BASE_H_