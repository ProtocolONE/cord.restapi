/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#include "RestApi/Auth/Vkontakte/VkontakteAuth.h"
#include <qdebug.h>

namespace GGS {
  namespace RestApi {
    namespace Auth {
      namespace Vkontakte {

        VkontakteAuth::VkontakteAuth()
          : _methodType("vkontakte"),
            _isAuthStarted(false)
        {
        }

        VkontakteAuth::~VkontakteAuth() 
        {
        }

        void VkontakteAuth::login()
        {
          this->_authStartedLock.lock();
          if (this->_isAuthStarted) {
            this->_authStartedLock.unlock();
            return;
          }

          this->_isAuthStarted = true;
          this->_authStartedLock.unlock();

          this->_view = new VkontakteWebView();
          this->_userPage = new UserAgentWebPage();
          this->_view->setPage(this->_userPage);
          
          // UNDONE: подумать все ли параметры полезны
          this->_view->page()->settings()->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,true);
          this->_view->page()->settings()->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,true);
          this->_view->page()->settings()->setAttribute(QWebSettings::LocalStorageEnabled,true);
          this->_view->page()->settings()->setAttribute(QWebSettings::AutoLoadImages,true);

          connect(this->_view->page()->networkAccessManager(), SIGNAL(sslErrors(QNetworkReply*,QList<QSslError>)), this, SLOT(sslErrors(QNetworkReply*,QList<QSslError>)));
          connect(this->_view, SIGNAL(loadFinished(bool)), this, SLOT(webPageLoadFinished(bool)));
          connect(this->_view, SIGNAL(titleChanged(QString)), this, SLOT(webPageTitleChanged(QString)));
          connect(this->_view, SIGNAL(windowClosed()), this, SLOT(webPageClosed()));

          QUrl url("http://api.vkontakte.ru/oauth/authorize");
          url.addQueryItem("client_id", this->_applicationId );
          url.addQueryItem("response_type", "code");
          url.addQueryItem("scope", "friends,offline");
          url.addQueryItem("display", "popup");
          url.addQueryItem("redirect_uri", this->_authReturnPath);

          this->_view->setWindowFlags(Qt::Tool);
          this->_view->load(url);
          this->_view->show();
        }

        void VkontakteAuth::setAuthResult(AuthResultCodes result)
        {
          this->_authStartedLock.lock();
          if (!this->_isAuthStarted) {
            this->_authStartedLock.unlock();
            return;
          }

          if(result == Success) 
             emit this->authResult(this->_credential);
          else
             emit this->authFailed(result);

          this->_isAuthStarted = false;
          this->_authStartedLock.unlock();
          this->_view->close();
          this->_userPage->deleteLater();
          this->_view->deleteLater();
        }

        void VkontakteAuth::sslErrors( QNetworkReply *reply, const QList<QSslError> &errors )
        {
          Q_FOREACH(QSslError error, errors) {
            WARNING_LOG << error;
          }
          
          // Так как сайт нам не подконтрольный подавляем все SSL ошибки.
          reply->ignoreSslErrors();
        }

        void VkontakteAuth::webPageLoadFinished(bool ok)
        {
          if(!ok) {
            this->setAuthResult(Cancel);
            return;
          }

           QUrl url = this->_view->url();

           if(url.host().compare("oauth.vkontakte.ru") == 0) {
             if(url.queryItemValue("cancel").compare("1") == 0) {
               this->setAuthResult(Cancel);
               return;
             }
           }
        }

        void VkontakteAuth::webPageTitleChanged(QString title)
        {
          QUrl titleUrl(title);
          if (!titleUrl.isValid())
            return;

          if (titleUrl.host().compare(this->_titleUrlHost) != 0)
            return;

          QUrl currentUrl = this->_view->url();
          if (currentUrl.hasQueryItem("error")
            && currentUrl.queryItemValue("error").compare("access_denied") == 0) {
              this->setAuthResult(Cancel);
              return;
          }

          if (titleUrl.hasQueryItem("isBlocked")
            && titleUrl.queryItemValue("isBlocked").compare("1") == 0) {
              this->setAuthResult(ServiceAccountBlocked);
              return;
          }
          
          QString userIdString;
          QString appKey;
          QString ga;
          if (titleUrl.hasQueryItem("userId")
            && titleUrl.hasQueryItem("appKey")
            && titleUrl.hasQueryItem("ga"))
          {
            userIdString = titleUrl.queryItemValue("userId");
            appKey = titleUrl.queryItemValue("appKey");
            ga = titleUrl.queryItemValue("ga");
          }

          if (userIdString.isEmpty()
            || appKey.isEmpty()
            || ga.isEmpty()) {
              this->setAuthResult(Cancel);
              return;
          }

          this->_credential.setUserId(userIdString);
          this->_credential.setAppKey(appKey);
          this->_credential.setCookie(ga);

          this->setAuthResult(Success);
        }

        void VkontakteAuth::webPageClosed()
        {
          this->setAuthResult(Cancel);
        }
      }
    }
  }
}