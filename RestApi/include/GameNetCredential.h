#ifndef _GGS_RESTAPI_GAMENETCREDENTIAL_H_
#define _GGS_RESTAPI_GAMENETCREDENTIAL_H_

#include "restapi_global.h"

#include <QtCore/QObject>
#include <QtCore/QString>

namespace GGS {
  namespace RestApi {
    class RESTAPI_EXPORT GameNetCredential : public QObject
    {
      Q_OBJECT
    public:
      GameNetCredential(void);
      ~GameNetCredential(void);
      
      GameNetCredential(const GameNetCredential &p);
      GameNetCredential &operator=(const GameNetCredential &p);

      const QString& appKey() const { return _appKey; }
      void setAppKey(const QString& val) { _appKey = val; }

      const QString& userId() const { return _userId; }
      void setUserId(const QString& val) { _userId = val; }

      const QString& cookie() const { return _cookie; }
      void setCookie(const QString& val) { _cookie = val; }

    private:
      QString _appKey;
      QString _userId;
      QString _cookie;
    };
  }
}

#endif // _GGS_RESTAPI_GAMENETCREDENTIAL_H_