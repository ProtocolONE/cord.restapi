/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef _GGS_RESTAPI_COMMAND_BASE_H_
#define _GGS_RESTAPI_COMMAND_BASE_H_

#include "restapi_global.h"

#include "CommandBaseInterface.h"
#include <QMetaObject>
#include <qdom.h>

namespace GGS {
	namespace RestApi {

		class RESTAPI_EXPORT CommandBase : public CommandBaseInterface 
		{
		public:
			CommandBase();
			~CommandBase();

			void setAuthRequire(bool isAuthRequire);
			void setCacheable(bool isCacheable);
			void setCacheTime(int cacheTime);
			void appendParameter(const QString& name, const QString& value);

			const QString& getGenericErrorMessage() { return this->genericErrorMessage; }
			const int getGenericErrorMessageCode() { return this->genericErrorMessageCode; }

			virtual const bool isRestapiOverrided() const { return this->_isRestapiOverrided; }

			virtual const QString& restapiUrl() const { return this->_restApiUrl; }

			bool isAuthRequire();
			bool isCacheable();

			int cacheTime();

			const QMap<QString, QString>* commandParameters() const;

			bool resultCallback( CommandResults commandResultCode, QString response );
      bool errorResultParse( CommandResults commandResultCode, QDomDocument response );
      virtual bool callMethod( CommandResults commandResultCode, QDomDocument response );
			void setRestapiUrl( const QString& url );

			virtual CommandResults resultCode(); 

		protected:
			CommandResults _resultCode;
			QString genericErrorMessage;
			int genericErrorMessageCode;

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