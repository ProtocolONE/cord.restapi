#include "CommandBase.h"


namespace GGS {
  namespace RestApi {

    CommandBase::CommandBase(void)
    {
      this->_isRestapiOverrided = false;
      this->_isAuthRequire = false;
      this->_isCacheable = false;
      this->_cacheTime = 0;
    }

    CommandBase::~CommandBase(void)
    {
    }

    bool CommandBase::isAuthRequire()
    {
      return this->_isAuthRequire;
    }

    bool CommandBase::isCacheable()
    {
      return this->_isCacheable;
    }

    int CommandBase::cacheTime()
    {
      return this->_cacheTime;
    }

    const QMap<QString, QString>* CommandBase::commandParameters() const
    {
      return &this->_commandParameters;
    }

    void CommandBase::resultCallback( CommandResults commandResultCode, QString response )
    {
      throw std::exception("The method or operation is not implemented.");
    }

    void CommandBase::setAuthRequire( bool isAuthRequire )
    {
      this->_isAuthRequire = isAuthRequire;
    }

    void CommandBase::setCacheable( bool isCacheable )
    {
      this->_isCacheable = isCacheable;
    }

    void CommandBase::setCacheTime( int cacheTime )
    {
      this->_cacheTime = cacheTime;
    }

    void CommandBase::appendParameter( const QString& name, const QString& value )
    {
      this->_commandParameters.insert(name, value);
    }

    void CommandBase::setRestapiUrl( const QString& url )
    {
      this->_restApiUrl = url;
      this->_isRestapiOverrided = true;
    }

    CommandBaseInterface::CommandResults CommandBase::resultCode()
    {
      return this->_resultCode;
    }

  }
}