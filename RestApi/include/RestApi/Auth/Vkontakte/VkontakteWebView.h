/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESAPI_AUTH_VKONTAKTE_VKONTAKTEWEBVIEW_H_
#define _GGS_RESAPI_AUTH_VKONTAKTE_VKONTAKTEWEBVIEW_H_

#include <QtWebKit/QWebView>

namespace GGS {
  namespace RestApi {
    namespace Auth {
      namespace Vkontakte {


        /// <summary>Класс переопределяет обычный QWebView для получения closeEvent. </summary>
        /// <remarks>Ilya.Tkachenko, 05.03.2012.</remarks>
        class VkontakteWebView : public QWebView
        {
          Q_OBJECT
        public:
          VkontakteWebView(void);
          ~VkontakteWebView(void);

        signals:
          void windowClosed();

        protected:
          virtual void closeEvent(QCloseEvent *event);
        };

      }
    }
  }
}

#endif // _GGS_RESAPI_AUTH_VKONTAKTE_VKONTAKTEWEBVIEW_H_