#pragma once

#include <RestApi/restapi_global.h>
#include <RestApi/CommandBase.h>
#include <RestApi/CacheInterface.h>

#include <QtCore/QObject>
#include <QtCore/QUrl>

namespace P1 {
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
      void finish(P1::RestApi::CommandBase::CommandResults results, QString response);
    
    protected:
      CacheInterface *_cache;
      bool _debugLogEnabled;
    };
  }
}
