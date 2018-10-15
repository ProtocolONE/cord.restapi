#pragma once

#include <RestApi/Command/CommandBase.h>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>

namespace P1 {
  namespace RestApi {
    namespace Command {
      class RESTAPI_EXPORT RestApiCommandBase : public CommandBase
      {
        Q_OBJECT
      public:
        explicit RestApiCommandBase(QObject *parent = 0);
        virtual ~RestApiCommandBase() = default;

        virtual void appendParameter(const QString& name, const QString& value);
        virtual const QMap<QString, QString>& commandParameters() const;

        const QString& method() const;
        void setMethod(const QString& value);

        bool supportPostRequest() const;
        int getRequestMaxLength() const;
        void setGetRequestMaxLength(int value);

      protected:
        QString _method;

        // INFO -1 - unsupported post request
        // If request length more than value than use post request.
        int _getRequestMaxLength;

        QMap<QString, QString> _commandParameters;

      };

    }
  }
}