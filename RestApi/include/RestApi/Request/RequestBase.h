#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/ProtocolOneCredential.h>

#include <QtCore/QObject>
#include <QtCore/QUrl>

namespace P1 {
  namespace RestApi {

    namespace Command {
      class CommandBase;
    }

    class CacheInterface;

    namespace Request {

      class RESTAPI_EXPORT RequestBase : public QObject
      {
        Q_OBJECT
      public:
        explicit RequestBase(QObject *parent = 0);
        virtual ~RequestBase();

        void setCommand(Command::CommandBase *command);

        virtual void setCache(CacheInterface *cache);
        virtual void setDebugLogEnabled(bool value);

        void execute();

        void updateCredential(const ProtocolOneCredential& credential);

      public slots:
        virtual void internalExecute() = 0;

      signals:
        void refreshAuth(const ProtocolOneCredential& credential);

      protected:
        void resultReceived();

        int _status;

        bool _debugLogEnabled;

        CacheInterface *_cache;
        Command::CommandBase *_command;
      };

    }
  }
}
