#pragma once

#include <RestApi/restapi_global.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QDateTime>

#include <QtCore/QSharedData>

namespace P1 {
  namespace RestApi {

    class RESTAPI_EXPORT ProtocolOneCredential
    {
    public:
      ProtocolOneCredential();
      ProtocolOneCredential(
        const QString& acccessTokent,
        const QDateTime& accessTokenExpiredTime, QObject *parent = 0);

      ProtocolOneCredential(
        const QString& acccessTokent,
        const QString& accessTokenExpiredTime, QObject *parent = 0);


      ProtocolOneCredential& operator=(const ProtocolOneCredential& other);
      bool operator==(const ProtocolOneCredential& other) const;
      bool operator!=(const ProtocolOneCredential& other) const;

      virtual ~ProtocolOneCredential();

      void clear();

      bool isEmpty() const;
      bool isValid() const;

      const QString& acccessTokent() const;
      void setAcccessTokent(const QString& val);

      const QDateTime& accessTokenExpiredTime() const;
      void setAccessTokenExpiredTime(const QDateTime& val);

      QString accessTokenExpiredTimeAsString() const;
      void setAccessTokenExpiredTime(const QString& val);

      const QString& userId() const;

    private:
      void parseToken();

      QString _userId;
      QString _acccessTokent;
      QDateTime _accessTokenExpiredTime;
    };

    Q_DECLARE_METATYPE(ProtocolOneCredential);
  }
}
