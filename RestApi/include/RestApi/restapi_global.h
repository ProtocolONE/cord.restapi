/****************************************************************************
** This file is a part of Syncopate Limited GameNet Application or it parts.
**
** Copyright (©) 2011 - 2012, Syncopate Limited and/or affiliates. 
** All rights reserved.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
****************************************************************************/

#ifndef RESTAPI_GLOBAL_H
#define RESTAPI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef RESTAPI_LIB
# define RESTAPI_EXPORT Q_DECL_EXPORT
#else
# define RESTAPI_EXPORT Q_DECL_IMPORT
#endif

#define WARNING_LOG qWarning() << __FILE__ << __LINE__ << __FUNCTION__

#endif // RESTAPI_GLOBAL_H
