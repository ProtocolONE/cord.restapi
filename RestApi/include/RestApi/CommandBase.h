#pragma once

#include <RestApi/restapi_global.h>

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QUrl>

class QDomDocument;

namespace P1 {
  namespace RestApi {
    class RestApiManager;
    /* Всегда пля подключения к этому сигналу, в параметрах необходимо
    указывать полный путь! Например
    connect( abc, SIGNAL( result(P1::RestApi::CommandBase::CommandResults ), ... ); // ПРАВИЛЬНО

    connect( abc, SIGNAL( result(CommandResults ), ... ); // НЕПРАВИЛЬНО, даже если CommandResults находится в области видимости

    Пример использования команд:

    ProtocolOneCredential auth;   // Класс для хранения авторизации
    auth.setAppKey(QString("92da94c6a632951c8d588f596826bfd1470843f0"));
    auth.setUserId("400001000000172890");

    HttpCommandRequest request;
    FakeCache cache;
    request.setCache(&cache); // Подключаем кэш

    RestApiManager restapi;

    restapi.setUri(QString("http://api.protocol.one/restapi"));
    restapi.setCridential(auth);
    restapi.setRequest(&request);

    // Подключаемся к сигналу результата. Данный сигнал будет вызван в любом случае, даже если
    // произошла какая-либо ошибка. В параметрах сигнала передается код выполнения команды.

    connect(&command, SIGNAL(result(P1::RestApi::CommandBase::CommandResults)),
    this,     SLOT(SetUserActivityResult(P1::RestApi::CommandBase::CommandResults)));


    // Задаем нужные нам параметры к команде
    command.setGameId(71);

    // Выполняем команду, после выполнения будет вызван сигнал result(P1::RestApi::CommandBase::CommandResults)
    // с соответствующим кодом.
    restapi.execute(&command);

    // После выполнения, для получения ответа от сервера, необходимо использовать геттер, для каждой команды свой.
    Например команда GetBalance, имеет один единственный геттер getBalance(), которым можно будет воспользоватся после
    выполнения команды.

    Например:

    restapi.execute(&command);

    ...

    void result(P1::RestApi::CommandBase::CommandResults code)
    {
    if (code == P1::RestApi::CommandBase::NoError)
    command.getBlance(); // возвратит баланс
    }

    Если у команды возвращаемых параметров много, то для этого случая мы их оборачиваем в т.н класс Response
    где групируем все данные. Например:

    void GetUserServiceAccount::GetUserServiceAccountResult( P1::RestApi::CommandBase::CommandResults code )
    {
    if (code == P1::RestApi::CommandBase::NoError){
    command.response()->getLogin(); // работаем с данными
    command.response()->getToken();
    command.response()->getStatus();
    command.response()->getPassword();
    } else if (code == P1::RestApi::CommandBase::GenericError)
    // реакция на ошибку
    }
    */
    class RESTAPI_EXPORT CommandBase : public QObject
    {
      Q_OBJECT
      Q_ENUMS(P1::RestApi::CommandBase::CommandResults);
      Q_ENUMS(P1::RestApi::CommandBase::Error);
      Q_FLAGS(RestApiErrors);

    public:
      enum CommandResults {
        NoError = 0,
        NetworkError = 1,
        GenericError = 2,
        XmlError = 3
      };

      enum Error {
        Unknown = 1,
        ToManyRequests = 2,
        InvalidRequest = 3,
        EulaNotAccepted = 10,
        IncorrectCaptcha = 11,
        CaptchaNotSpecified = 12, 
        AuthorizationFailed = 100,
        AccountNotExists = 101,
        ServiceAccountBlocked = 102,
        AuthorizationLimitExceed = 103,
        UnknownAccountStatus = 104,
        IncorrectAccountPassword = 105,
        IncorrectEmailFormat = 110,
        EmailAlreadyExists = 111,
        IncorrectPasswordFormat = 112,
        IncorrectPasswordRepeat = 113,
        IncorrectNicknameformat = 114,
        NicknameAlreadyExists = 115,
        IncorrectTechnameFormat = 116,
        TechnameAlreadyExists = 117,
        UnableChangeTechname = 118,
        UnableChangeNickname = 119,
        UnableChangeEmail = 220,
        NicknameNotSpecified = 121,
        TechnameNotSpecified = 122,
        NicknameForbidden = 123,
        TechnameForbidden = 124,
        ServiceAuthorizationImpossible = 125,
        PhoneIncorrectCode = 126,
        PhoneAlreadyInUse = 127,
        PhoneUnableDeliverSms = 128,
        PhonePhoneFormat = 129,
        PhoneBlocked = 130,
        GuestExpired = 131,
        RequestParameterMissing = 200,
        RequestWrongAuthType = 201,
        RequestWrongServiceId = 202,
        RequestWorngAuthId = 203,
        RequestUnknownMethod = 204,
        SellingTransactionWrongNumber = 230,
        SellingTransactionPersonalAccount = 231,
        SellingWrongItemCost = 250,
        SellingItemNotForSelling = 251,
        SellingNoEnoughMoney = 252,
        SellingRejectedByService = 253,
        SellingItemNotFound = 254,
        SellingAccountNotFound = 255,
        ImageNotExists = 300,
        ImageUnknownFileType = 301,
        ImageWrongType = 302,
        ImageResizeFailed = 303,
        PromoKeyWrong = 400,
        PromoKeyExpired = 401,
        PromoAlreadyHaveSubscribtion = 402,
        FriendToThemselfDenied = 500,
        FriendshipAlreadyExists = 501,
        FriendRequestAlreadyExists = 502,
        FriendRequestDailyLimit = 503,
        PakkanenPermissionDenied = 601,
        PakkanenVkVerification = 602,
        PakkanenPhoneVerification = 603,
        PakkanenVkPhoneVerification = 604,
        PakkanenGeoIpBlocked = 605,
      };

      Q_DECLARE_FLAGS(RestApiErrors, Error)

      explicit CommandBase(QObject *parent = 0);
      virtual ~CommandBase();

      void setAuthRequire(bool isAuthRequire);
      virtual bool isAuthRequire();

      void setCacheable(bool isCacheable);
      virtual bool isCacheable();

      void setCacheTime(int cacheTime);
      virtual int cacheTime();

      void setVersion(const QString &version);

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
      void resultCallback(P1::RestApi::CommandBase::CommandResults commandResultCode, QString response);

      void execute();
      void execute(RestApiManager *manager);

    protected:
      QString _errorMessage;
      int _errorCode;

    private:
      bool _isAuthRequire;
      bool _isCacheable;
      int _cacheTime;

      QString _restApiUrl;
      bool _isRestapiOverrided;
      
      QMap<QString, QString> _commandParameters;

    signals:
      void result(P1::RestApi::CommandBase::CommandResults);
      void genericError(P1::RestApi::CommandBase::Error error, QString message);
    };
  }
}

Q_DECLARE_METATYPE(P1::RestApi::CommandBase::CommandResults);
Q_DECLARE_METATYPE(P1::RestApi::CommandBase::Error);
