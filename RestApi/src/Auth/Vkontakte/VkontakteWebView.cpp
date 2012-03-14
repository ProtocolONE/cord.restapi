/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/
#include "Auth/Vkontakte/VkontakteWebView.h"

namespace GGS {
  namespace RestApi {
    namespace Auth {
      namespace Vkontakte {

        VkontakteWebView::VkontakteWebView(void)
        {
        }


        VkontakteWebView::~VkontakteWebView(void)
        {
        }

        void VkontakteWebView::closeEvent( QCloseEvent *event )
        {
          emit this->windowClosed();
        }

      }
    }
  }
}