/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include <RestApi/CommandBase.h>

#include <QtCore/QDebug>
#include <QtXml/QDomDocument>

namespace GGS {
  namespace RestApi {

    CommandBase::CommandBase(QObject *parent/*=0*/) 
      : QObject(parent),
        _restApiUrl("https://api.gamenet.ru/restapi"),
        _isRestapiOverrided(false),
        _isAuthRequire(false),
        _isCacheable(false),
        _cacheTime(0)
    {
      this->genericErrorMessage = QString();
      this->genericErrorMessageCode = 0;

      qRegisterMetaType<GGS::RestApi::CommandBase::CommandResults>("GGS::RestApi::CommandBase::CommandResults");
    }

    CommandBase::~CommandBase(){
    }

    bool CommandBase::isAuthRequire()
    {
      return this->_isAuthRequire;
    }

    bool CommandBase::isCacheable(){
      return this->_isCacheable;
    }

    int CommandBase::cacheTime() {
      return this->_cacheTime;
    }

    const QMap<QString, QString>* CommandBase::commandParameters() const {
      return &this->_commandParameters;
    }

    void CommandBase::resultCallback(GGS::RestApi::CommandBase::CommandResults commandResultCode, QString response ) 
    {  
      QObject::sender()->deleteLater();

      if(commandResultCode != NoError) {
        emit this->result(commandResultCode);
        return;
      }
      QDomDocument doc;
      if (!doc.setContent(response)) {
        emit this->result(XmlError);
        return;
      }

      if (this->errorResultParse(doc)){
        emit this->result(GenericError);
        return;
      }

      if (this->callMethod(doc)){
        emit this->result(XmlError);
        return;
      }

      emit this->result(NoError);
    }

    bool CommandBase::errorResultParse( const QDomDocument& response ){
      QDomElement responseElement = response.documentElement();
      QDomElement errorElement = responseElement.firstChildElement("error");
      QDomElement errorMessage  = errorElement.firstChildElement("message");
      QDomElement errorCode  = errorElement.firstChildElement("code");

      if (!errorMessage.isNull() || !errorCode.isNull()){
        genericErrorMessage = errorMessage.text();
        genericErrorMessageCode = errorCode.text().toInt();
        return true;
      }
      return false;
    }

    bool CommandBase::callMethod( const QDomDocument& response ){
      return true;
    }

    void CommandBase::setAuthRequire( bool isAuthRequire ) {
      this->_isAuthRequire = isAuthRequire;
    }

    void CommandBase::setCacheable( bool isCacheable ) {
      this->_isCacheable = isCacheable;
    }

    void CommandBase::setCacheTime( int cacheTime ) {
      this->_cacheTime = cacheTime;
    }

    void CommandBase::appendParameter( const QString& name, const QString& value ) {
      this->_commandParameters.insert(name, value);
    }

    void CommandBase::setRestapiUrl( const QString& url )  {
      this->_restApiUrl = url;
      this->_isRestapiOverrided = true;
    }

    const QString& CommandBase::getGenericErrorMessage()
    {
      return this->genericErrorMessage;
    }

    const int CommandBase::getGenericErrorMessageCode()
    {
      return this->genericErrorMessageCode;
    }

    const QString& CommandBase::errorMessage()
    {
      return this->genericErrorMessage;
    }

    const int CommandBase::errorCode()
    {
      return this->genericErrorMessageCode;
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
      QUrl request(this->_restApiUrl);

      QMap<QString, QString>::const_iterator it = this->_commandParameters.begin();
      QMap<QString, QString>::const_iterator end = this->_commandParameters.end();

      for(;it != end; ++it)
        request.addQueryItem(it.key(), it.value());

      return request;
    }



  }
}