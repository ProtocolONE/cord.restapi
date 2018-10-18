#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/ProtocolOneCredential.h>

#include <RestApi/Request/RequestFactory.h>

#include <RestApi/Command/CommandBase.h>
#include <RestApi/RefreshTokenManager.h>

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QPointer>

namespace P1 {
  namespace RestApi {
    class CacheInterface;

    namespace Command {
      class CommandBase;
    }

    class RESTAPI_EXPORT RestApiManager : public QObject
    {
      Q_OBJECT
    public:
      explicit RestApiManager(QObject *parent = 0);
      virtual ~RestApiManager();

      void setUri(const QString& uri);

      Q_INVOKABLE void execute(Command::CommandBase *command);

      void setCridential(const ProtocolOneCredential &credential);
      void setCache(CacheInterface *cache);
      void setDebugLogEnabled(bool value);

      const ProtocolOneCredential &credential();

      void updateCredential(const ProtocolOneCredential &old, const ProtocolOneCredential &value);

      static void setCommonInstance(RestApiManager *instance);
      static RestApiManager* commonInstance();

    signals:
      void authorizationError(const ProtocolOneCredential &credential, const Command::CommandBase *command);

    private:
      void onCommandResult();
      void onRefreshTokentRequest(const ProtocolOneCredential& value);

      Request::RequestFactory _factory;
      
      QString _uri;
      ProtocolOneCredential _credential;
      CacheInterface *_cache;
      RefreshTokenManager _refreshManger;

      bool _debugLogEnabled;

      static RestApiManager* _commonInstance;

    };
  }
}
