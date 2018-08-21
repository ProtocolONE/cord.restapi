#pragma once

#include <QtCore/qglobal.h>

#ifdef RESTAPI_STATIC_LIB
# define RESTAPI_EXPORT 
#else

#ifdef RESTAPI_LIB
# define RESTAPI_EXPORT Q_DECL_EXPORT
#else
# define RESTAPI_EXPORT Q_DECL_IMPORT
#endif

#endif

#define WARNING_LOG qWarning() << __FILE__ << __LINE__ << __FUNCTION__

