/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESAPI_AUTH_VKONTAKTE_USERAGENTWEBPAGE_H_
#define _GGS_RESAPI_AUTH_VKONTAKTE_USERAGENTWEBPAGE_H_

#include <QtWebKit/QWebPage>

namespace GGS {
  namespace RestApi {
    namespace Auth {
      namespace Vkontakte {


        /// <summary>Класс реализует переопределение строки user agent для браузера. </summary>
        /// <remarks>Ilya.Tkachenko, 27.02.2012.</remarks>
        class UserAgentWebPage : public QWebPage
        {
          Q_OBJECT
        public:
          UserAgentWebPage(void);
          ~UserAgentWebPage(void);


          /// <summary>При необходимости можно вынести строку юзерагента в настраиваемую переменную. На данный момент маскируемся под chrome с тегом GNA.</summary>
          /// <remarks>Ilya.Tkachenko, 27.02.2012.</remarks>
          /// <param name="url">URL of the document.</param>
          /// <returns>Строка user agent.</returns>
          QString userAgentForUrl(const QUrl &url ) const {
            return QString("Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/535.11 (KHTML, like Gecko) Chrome/17.0.963.46 Safari/535.11 GNA ");
          }
        };

      }
    }
  }
}

#endif // _GGS_RESAPI_AUTH_VKONTAKTE_USERAGENTWEBPAGE_H_