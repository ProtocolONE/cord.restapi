#ifndef _GGS_RESTAPI_COMMAND_BASE_H_
#define _GGS_RESTAPI_COMMAND_BASE_H_

#include "restapi_global.h"

#include "CommandBaseInterface.h"

namespace GGS {
  namespace RestApi {

    class RESTAPI_EXPORT CommandBase : public CommandBaseInterface
    {
    public:
      CommandBase(void);
      ~CommandBase(void);

      void setAuthRequire(bool isAuthRequire);
      void setCacheable(bool isCacheable);
      void setCacheTime(int cacheTime);
      void appendParameter(const QString& name, const QString& value);

      virtual const bool isRestapiOverrided() const { return this->_isRestapiOverrided; };

      virtual const QString& restapiUrl() const { return this->_restApiUrl; }

      bool isAuthRequire();

      bool isCacheable();

      int cacheTime();

      const QMap<QString, QString>* commandParameters() const;

      virtual void resultCallback( CommandResults commandResultCode, QString response );

      void setRestapiUrl( const QString& url );

      virtual CommandResults resultCode();

    protected:
      CommandResults _resultCode;

    private:
      bool _isAuthRequire;
      bool _isCacheable;
      int _cacheTime;

      QString _restApiUrl;
      bool _isRestapiOverrided;

      QMap<QString, QString> _commandParameters;
    };

  }
}
#endif // _GGS_RESTAPI_COMMAND_BASE_H_