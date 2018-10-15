#include <RestApi/Command/JsonCommand.h>
#include <RestApi/Request/RequestFactory.h>

#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>

namespace P1 {
  namespace RestApi {
    namespace Command {

      JsonCommand::JsonCommand(QObject *parent /*= 0*/)
        : CommandBase(parent)
      {
        this->_type = Request::RequestFactory::Json;
      }

      const QString& JsonCommand::method() const
      {
        return this->_method;
      }

      void JsonCommand::setMethod(const QString& value)
      {
        this->_method = value;
      }

      QByteArray JsonCommand::postData()
      {
        QByteArray result;
       
        QJsonDocument doc = QJsonDocument::fromVariant(this->_params);
        if (!doc.isNull())
          result = doc.toJson(QJsonDocument::Compact);

        return result;
      }

    }
  }
}