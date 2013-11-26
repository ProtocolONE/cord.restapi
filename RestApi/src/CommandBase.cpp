/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (�) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <RestApi/CommandBase.h>
#include <RestApi/RestApiManager>

#include <QtCore/QDebug>
#include <QtCore/QUrlQuery>
#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {

    CommandBase::CommandBase(QObject *parent/*=0*/) 
      : QObject(parent),
        _restApiUrl("https://gnapi.com:8443/restapi"),
        _isRestapiOverrided(false),
        _isAuthRequire(false),
        _isCacheable(false),
        _cacheTime(0)
    {
      this->_errorMessage = QString();
      this->_errorCode = 0;
    }

    CommandBase::~CommandBase()
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

    void CommandBase::resultCallback(GGS::RestApi::CommandBase::CommandResults commandResultCode, QString response) 
    {  
      QObject::sender()->deleteLater();

      if (commandResultCode != NoError) {
        emit this->result(commandResultCode);
        return;
      }

      QDomDocument doc;
      if (!doc.setContent(response)) {
        emit this->result(XmlError);
        return;
      }

      if (this->errorResultParse(doc)) {
        emit this->result(GenericError);
        return;
      }

      if (this->callMethod(doc)) {
        emit this->result(XmlError);
        return;
      }

      emit this->result(NoError);
    }

    bool CommandBase::errorResultParse(const QDomDocument& response)
    {
      QDomElement responseElement = response.documentElement();
      QDomElement errorElement = responseElement.firstChildElement("error");
      QDomElement errorMessage  = errorElement.firstChildElement("message");
      QDomElement errorCode  = errorElement.firstChildElement("code");

      if (!errorMessage.isNull() || !errorCode.isNull()) {
        this->_errorMessage = errorMessage.text();
        this->_errorCode = errorCode.text().toInt();
        emit this->genericError(static_cast<Error>(_errorCode), _errorMessage);
        return true;
      }

      return false;
    }

    bool CommandBase::callMethod(const QDomDocument& response)
    {
      return true;
    }

    void CommandBase::setAuthRequire(bool isAuthRequire)
    {
      this->_isAuthRequire = isAuthRequire;
    }

    void CommandBase::setCacheable(bool isCacheable)
    {
      this->_isCacheable = isCacheable;
    }

    void CommandBase::setCacheTime(int cacheTime)
    {
      this->_cacheTime = cacheTime;
    }

    void CommandBase::appendParameter(const QString& name, const QString& value)
    {
      this->_commandParameters.insert(name, value);
    }

    void CommandBase::setRestapiUrl(const QString& url)
    {
      this->_restApiUrl = url;
      this->_isRestapiOverrided = true;
    }

    const QString& CommandBase::getGenericErrorMessage()
    {
      return this->_errorMessage;
    }

    const int CommandBase::getGenericErrorMessageCode()
    {
      return this->_errorCode;
    }

    const QString& CommandBase::errorMessage()
    {
      return this->_errorMessage;
    }

    const int CommandBase::errorCode()
    {
      return this->_errorCode;
    }

    const bool CommandBase::isRestapiOverrided() const
    {
      return this->_isRestapiOverrided;
    }

    const QString& CommandBase::restapiUrl() const
    {
      return this->_restApiUrl;
    }

    const QUrl CommandBase::url()
    {
      QUrl request;
      request.setUrl(this->_restApiUrl);

      QMap<QString, QString>::const_iterator it = this->_commandParameters.begin();
      QMap<QString, QString>::const_iterator end = this->_commandParameters.end();

      QUrlQuery params;
      for(;it != end; ++it)
        request.addEncodedQueryItem(QUrl::toPercentEncoding(it.key()), QUrl::toPercentEncoding(it.value()));
        params.addQueryItem(it.key(), it.value());

      request.setQuery(params);

      return request;
    }

    void CommandBase::setVersion(const QString &version)
    {
      this->appendParameter("version", version);
    }

    void CommandBase::execute()
    {
      RestApiManager *manager = RestApiManager::commonInstance();
      Q_CHECK_PTR(manager);
      this->execute(manager);
    }

    void CommandBase::execute(RestApiManager *manager)
    {
      manager->execute(this);
    }
  }
}