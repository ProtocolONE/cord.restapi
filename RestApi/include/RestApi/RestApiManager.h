#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/ProtocolOneCredential.h>
#include <RestApi/RequestFactory.h>
#include <RestApi/CommandBase.h>

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QPointer>

namespace P1 {
  namespace RestApi {
    class CacheInterface;

    class RESTAPI_EXPORT RestApiManager : public QObject
    {
      Q_OBJECT
    public:
      RestApiManager(QObject *parent = 0);
      ~RestApiManager();

      /// <summary>������ ����� ������� �������.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="uri">Url �� ������������ �������.</param>
      void setUri(const QString& uri);

      /// <summary>������������� �����, ����� ������� ����������� ����������� ��������.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="request">[in] If non-null, the request.</param>
      void setRequest(RequestFactory::RequestType type);

      /// <summary>��������� ��������.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="command">[in] If non-null, the command.</param>
      Q_INVOKABLE void execute(CommandBase *command);

      /// <summary>������ ����������� ��� ��� �������.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="credential">The credential.</param>
      void setCridential(const ProtocolOneCredential &credential);

      void setCache(CacheInterface *cache);

      void setDebugLogEnabled(bool value);

      /*!
        \fn credential
        \brief ���������� ������� ������ � ������� ������������.
      */
      const ProtocolOneCredential &credential();

      static void setCommonInstance(RestApiManager *instance);
      static RestApiManager* commonInstance();

    signals:
      __declspec(deprecated("migrate to genericErrorEx and rename it to genericError"))
      void genericError(P1::RestApi::CommandBase::Error, QString message);
      void genericErrorEx(P1::RestApi::CommandBase::Error, QString message, CommandBase *command);

    private:
      void onGenericError(P1::RestApi::CommandBase::Error error, QString message);

      RequestFactory _factory;
      RequestFactory::RequestType _type;
      QString _uri;
      ProtocolOneCredential _credential;
      CacheInterface *_cache;

      bool _debugLogEnabled;

      static RestApiManager* _commonInstance;

    };
  }
}
