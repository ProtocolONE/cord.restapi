#pragma once

#include <RestApi/restapi_global.h>

#include <QtCore/QObject>
#include <QtCore/QString>

namespace P1 {
  namespace RestApi {
    class RESTAPI_EXPORT GameNetCredential : public QObject
    {
      Q_OBJECT
    public:
      GameNetCredential();
      ~GameNetCredential();
      
      GameNetCredential(const GameNetCredential &p);
      GameNetCredential &operator=(const GameNetCredential &p);
      bool operator==(const GameNetCredential& rhs) const;

      /**
       * \fn  bool GameNetCredential::isEmpty() const;
       *
       * \brief Проверяет заполнена ли структура. Метод проверяет заполнение ТОЛЬКО userId.
       *        Если необходимо проверка остальных полей, проверяйте их отдельно.
       *
       * \author  Ilya Tkachenko
       * \date  25.09.2014
       *
       * \return  true если userId пустой, иначе false.
       */

      bool isEmpty() const;

      const QString& appKey() const;
      void setAppKey(const QString& val);

      const QString& userId() const;
      void setUserId(const QString& val);

      const QString& cookie() const;
      void setCookie(const QString& val);

    private:
      QString _appKey;
      QString _userId;
      QString _cookie;
    };

  }
}
