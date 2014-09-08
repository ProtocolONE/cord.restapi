/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_GAMENETCREDENTIAL_H_
#define _GGS_RESTAPI_GAMENETCREDENTIAL_H_

#include <RestApi/restapi_global.h>

#include <QtCore/QObject>
#include <QtCore/QString>

namespace GGS {
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
#endif // _GGS_RESTAPI_GAMENETCREDENTIAL_H_