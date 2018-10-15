#include <RestApi/Command/RestApiCommandBase.h>

#include <RestApi/Request/RequestFactory.h>

namespace P1 {
  namespace RestApi {
    namespace Command {

      RestApiCommandBase::RestApiCommandBase(QObject *parent /*= 0*/)
        : CommandBase(parent)
        , _getRequestMaxLength(-1)
      {
        this->_type = Request::RequestFactory::UrlEncoded;
      }

      void RestApiCommandBase::appendParameter(const QString& name, const QString& value)
      {
        this->_commandParameters.insert(name, value);
      }

      const QMap<QString, QString>& RestApiCommandBase::commandParameters() const
      {
        return this->_commandParameters;
      }

      const QString& RestApiCommandBase::method() const
      {
        return this->_method;
      }

      void RestApiCommandBase::setMethod(const QString& value)
      {
        this->_method = value;
      }

      bool RestApiCommandBase::supportPostRequest() const
      {
        return this->_getRequestMaxLength > 0;
      }

      int RestApiCommandBase::getRequestMaxLength() const
      {
        return this->_getRequestMaxLength;
      }

      void RestApiCommandBase::setGetRequestMaxLength(int value)
      {
        this->_getRequestMaxLength = value;
      }

    }
  }
}