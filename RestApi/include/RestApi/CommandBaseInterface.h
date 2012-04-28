/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMAND_BASE_INTERFACE_H_
#define _GGS_RESTAPI_COMMAND_BASE_INTERFACE_H_

#include <RestApi/restapi_global.h>

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMap>

class QDomDocument;

namespace GGS {
  namespace RestApi {

    class RESTAPI_EXPORT CommandBaseInterface {
    public:
      Q_ENUMS(GGS::RestApi::CommanBaseInterface::CommandResults);

      enum CommandResults{
        NoError = 0,
        NetworkError = 1,
        GenericError = 2,
        XmlError = 3
      };

      virtual ~CommandBaseInterface() {};


      /// <summary>Query if this object is authorisation require.</summary>
      /// <remarks>Ilya.Tkachenko, 10.02.2012.</remarks>
      /// <returns>true if authorisation require, false if not.</returns>
      virtual bool isAuthRequire() = 0;


      /// <summary>Query if this object is cacheable.</summary>
      /// <remarks>Ilya.Tkachenko, 10.02.2012.</remarks>
      /// <returns>true if cacheable, false if not.</returns>
      virtual bool isCacheable() = 0;


      /// <summary>Gets the cache time.</summary>
      /// <remarks>Ilya.Tkachenko, 10.02.2012.</remarks>
      /// <returns>The cache time.</returns>
      virtual int cacheTime() = 0;  


      /// <summary>Gets the command parameters.</summary>
      /// <remarks>Ilya.Tkachenko, 10.02.2012.</remarks>
      /// <returns>null if it fails, else the command parameters.</returns>
      virtual const QMap<QString, QString>* commandParameters() const = 0;


      /// <summary>Callback, called when the result.</summary>
      /// <remarks>Ilya.Tkachenko, 10.02.2012.</remarks>
      /// <param name="commandResult">The command result.</param>
      /// <param name="response">     The response.</param>
      /// <param name="return bool">  Is error.</param>
      virtual bool resultCallback(CommandResults commandResultCode, QString response) = 0;
      virtual bool errorResultParse(const QDomDocument& response) = 0;
      virtual bool callMethod(const QDomDocument& response) = 0;

      virtual void setRestapiUrl(const QString& url) = 0;

      virtual const bool isRestapiOverrided() const = 0;

      virtual const QString& restapiUrl() const = 0;

      virtual void appendParameter(const QString& name, const QString& value) = 0;
    };
  }
}
#endif // _GGS_RESTAPI_COMMAND_BASE_INTERFACE_H_