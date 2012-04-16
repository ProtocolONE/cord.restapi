/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/CommandBase.h"

#include <iostream>
#include <qdebug.h>
#include <qdom.h>

namespace GGS {
  namespace RestApi {

    CommandBase::CommandBase() {
      this->_isRestapiOverrided = false;
      this->_isAuthRequire = false;
      this->_isCacheable = false;
      this->_cacheTime = 0;
      this->genericErrorMessage = QString();
      this->genericErrorMessageCode = 0;
	  this->_resultCode = NoError;
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

    bool CommandBase::resultCallback( CommandResults commandResultCode, QString response ) {  
      if(commandResultCode != CommandBaseInterface::NoError) {
        this->_resultCode = commandResultCode;
        return true;
      }
      QDomDocument doc;
      if (!doc.setContent(response)) {
        this->_resultCode = CommandBaseInterface::XmlError;
        return true;
      }

      if (errorResultParse(commandResultCode, doc))
        return true;

      if (callMethod(commandResultCode, doc))
        return true;


      return false;
    }

    bool CommandBase::errorResultParse( CommandResults commandResultCode, QDomDocument response ){
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

    bool CommandBase::callMethod( CommandResults commandResultCode, QDomDocument response ){
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

    CommandBaseInterface::CommandResults CommandBase::resultCode()  {
      return this->_resultCode;
    }

  }
}