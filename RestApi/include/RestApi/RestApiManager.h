#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/GameNetCredential.h>
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

      /// <summary>Задает адрес рестапи сервера.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="uri">Url до рестапишного сервера.</param>
      void setUri(const QString& uri);

      /// <summary>Устанавливает класс, через который выполняются рестапишные комманды.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="request">[in] If non-null, the request.</param>
      void setRequest(RequestFactory::RequestType type);

      /// <summary>Выполняет комманду.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="command">[in] If non-null, the command.</param>
      Q_INVOKABLE void execute(CommandBase *command);

      /// <summary>Задает авторизацию для все комманд.</summary>
      /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
      /// <param name="credential">The credential.</param>
      void setCridential(const GameNetCredential &credential);

      void setCache(CacheInterface *cache);

      void setDebugLogEnabled(bool value);

      /*!
        \fn credential
        \brief Возвращает текущий объект с данными авторизациию.
      */
      const GameNetCredential &credential();

      static void setCommonInstance(RestApiManager *instance);
      static RestApiManager* commonInstance();

    signals:
      __declspec(deprecated("QGNA-1011 migrate to genericErrorEx and rename it to genericError"))
      void genericError(P1::RestApi::CommandBase::Error, QString message);
      void genericErrorEx(P1::RestApi::CommandBase::Error, QString message, CommandBase *command);

    private:
      void onGenericError(P1::RestApi::CommandBase::Error error, QString message);

      RequestFactory _factory;
      RequestFactory::RequestType _type;
      QString _uri;
      GameNetCredential _credential;
      CacheInterface *_cache;

      bool _debugLogEnabled;

      static RestApiManager* _commonInstance;

    };
  }
}
