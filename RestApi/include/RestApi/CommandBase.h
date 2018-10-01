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

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QUrl>

class QDomDocument;

namespace GGS {
  namespace RestApi {
    class RestApiManager;
    /* ������ ��� ����������� � ����� �������, � ���������� ����������
    ��������� ������ ����! ��������
    connect( abc, SIGNAL( result(GGS::RestApi::CommandBase::CommandResults ), ... ); // ���������

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

    connect(&command, SIGNAL(result(GGS::RestApi::CommandBase::CommandResults)),
    this,     SLOT(SetUserActivityResult(GGS::RestApi::CommandBase::CommandResults)));


    // ������ ������ ��� ��������� � �������
    command.setGameId(71);

    // ��������� �������, ����� ���������� ����� ������ ������ result(GGS::RestApi::CommandBase::CommandResults)
    // � ��������������� �����.
    restapi.execute(&command);

    // ����� ����������, ��� ��������� ������ �� �������, ���������� ������������ ������, ��� ������ ������� ����.
    �������� ������� GetBalance, ����� ���� ������������ ������ getBalance(), ������� ����� ����� �������������� �����
    ���������� �������.

    ��������:

    restapi.execute(&command);

    ...

    void result(GGS::RestApi::CommandBase::CommandResults code)
    {
    if (code == GGS::RestApi::CommandBase::NoError)
    command.getBlance(); // ��������� ������
    }

    ���� � ������� ������������ ���������� �����, �� ��� ����� ������ �� �� ����������� � �.� ����� Response
    ��� ��������� ��� ������. ��������:

    void GetUserServiceAccount::GetUserServiceAccountResult( GGS::RestApi::CommandBase::CommandResults code )
    {
    if (code == GGS::RestApi::CommandBase::NoError){
    command.response()->getLogin(); // �������� � �������
    command.response()->getToken();
    command.response()->getStatus();
    command.response()->getPassword();
    } else if (code == GGS::RestApi::CommandBase::GenericError)
    // ������� �� ������
    }
    */
    class RESTAPI_EXPORT CommandBase : public QObject
    {
      Q_OBJECT
      Q_ENUMS(GGS::RestApi::CommandBase::CommandResults);
      Q_ENUMS(GGS::RestApi::CommandBase::Error);
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
      void resultCallback(GGS::RestApi::CommandBase::CommandResults commandResultCode, QString response);

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
      void result(GGS::RestApi::CommandBase::CommandResults);
      void genericError(GGS::RestApi::CommandBase::Error error, QString message);
    };
  }
}

Q_DECLARE_METATYPE(GGS::RestApi::CommandBase::CommandResults);
Q_DECLARE_METATYPE(GGS::RestApi::CommandBase::Error);

#endif // _GGS_RESTAPI_COMMAND_BASE_H_