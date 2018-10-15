#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/ProtocolOneCredential.h>

#include <QtCore/QObject>
#include <QtCore/QMetaType>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QUrl>

#include <stdint.h>

namespace P1 {
  namespace RestApi {
    namespace Request {
      class RequestBase;
    }

    class RestApiManager;
  
    namespace Command {
      class RESTAPI_EXPORT CommandBase : public QObject
      {
        Q_OBJECT
      public:
        enum CommandResults : uint32_t {
          // Generic errors:
          Success = 0,
          UnknownEror = 1,
          Unauthorized = 2,
          NetworkError = 3,
          BadFormat = 4,

          CommandCustom = 0x1000,

          NotUsed = 0xffffffff
        };

        explicit CommandBase(QObject *parent = 0);
        virtual ~CommandBase();

        void setAuthRequire(bool isAuthRequire);
        virtual bool isAuthRequire();

        void setCacheable(bool isCacheable);
        virtual bool isCacheable();

        void setCacheTime(int cacheTime);
        virtual int cacheTime();

        const QString& version() const;
        void setVersion(const QString &version);

        virtual void setApiUrl(const QString& url);
        virtual const QString& apiUrl() const;

        const QString& errorMessage() const;

        const int errorCode() const;
        void setErrorCode(int value);

        bool isSuccess() const;

        const ProtocolOneCredential& credential() const;
        void setCredential(const ProtocolOneCredential& value);
        bool hasCredential() const;

        int type() const;
        void setType(int value);

        int statusCode() const;
        void setStatusCode(int value);

        virtual void setResponse(const QByteArray& data);

      signals:
        void result();

      public slots:
        void execute();
        void execute(RestApiManager *manager);

      protected:
        void setError(int statusCode, int commandResult);

        QMap<int, int> _errorCodeMap;

        int _type;

        QString _version;

        QString _errorMessage;
        int _errorCode;
        int _statusCode;

        ProtocolOneCredential _credential;

        bool _isAuthRequire;
        bool _isCacheable;
        int _cacheTime;

        QString _apiUrl;

      private:
        friend class Request::RequestBase;
        void resultRecevied();
      };

    }
  }
}

Q_DECLARE_METATYPE(P1::RestApi::Command::CommandBase::CommandResults);

