#pragma once

#include <RestApi/Command/CommandBase.h>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QVariantMap>

namespace P1 {
  namespace RestApi {
    namespace Command {

      class RESTAPI_EXPORT JsonCommand : public CommandBase
      {
        Q_OBJECT
      public:
        explicit JsonCommand(QObject *parent = 0);
        virtual ~JsonCommand() = default;

        const QString& method() const;
        void setMethod(const QString& value);

        QByteArray postData();

      protected:
        QString _method;
        QVariantMap _params;
      };

    }
  }
}