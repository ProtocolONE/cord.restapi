/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2017, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>
#include <RestApi/CacheInterface.h>

#include <QtCore/QObject>
#include <QtCore/QUrl>

namespace GGS {
  namespace RestApi {
    /*!
      \class RequestBase
    
      \brief Request interface. Реализация класса обязана быть реинтерабельной.
    */
    class RESTAPI_EXPORT RequestBase : public QObject
    {
      Q_OBJECT
    public:
      explicit RequestBase(QObject *parent = 0);
      virtual ~RequestBase();

      virtual void setCache(CacheInterface *cache);
      virtual void setDebugLogEnabled(bool value);

    public slots:
      virtual void execute(const QUrl &request) = 0;
    
    signals:
      void finish(GGS::RestApi::CommandBase::CommandResults results, QString response);
    
    protected:
      CacheInterface *_cache;
      bool _debugLogEnabled;
    };
  }
}
